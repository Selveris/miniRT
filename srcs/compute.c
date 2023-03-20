#include <math.h>
#include <float.h>
#include "miniRT.h"

#include <stdio.h>

static double	compute_closest_intersect(t_scene const *scene,
		t_ray const *ray, t_intersect *m_intersect)
{
	t_list		*objs;
	double		m_dist;
	t_intersect	intersect;
	double		dist;

	m_intersect->obj = NULL;
	m_dist = DBL_MAX;
	objs = scene->objs;
	while (objs)
	{
		dist = obj_intersect[((t_obj *)objs->content)->type](ray,
					objs->content, &intersect);
		if (dist >= 0 && dist < m_dist)
		{
			m_dist = dist;
			*m_intersect = intersect;
		}
		objs = objs->next;	
	}
	if (m_intersect->obj)
		return (m_dist);
	return (-1);
}

static int	in_shadow(t_scene const *scene, t_intersect const *intersect,
		t_light const *light)
{
	t_intersect	m_intersect;
	double		m_dist;
	double		l_dist;
	t_ray		ray;

	l_dist = v_distance_to(intersect->point, light->origin);
	ray.origin = intersect->point;
	ray.dir = v_direction_to(intersect->point, light->origin);
	ray.origin = ray_forward(&ray, O_MIN_DIST);
	m_dist = compute_closest_intersect(scene, &ray, &m_intersect);
	if (m_dist >= 0 && m_dist < l_dist)
		return (1);
	return (0);
}

static t_color	compute_phong(t_scene const *scene, t_list *lights, 
		t_intersect const *intersect, t_v3 view_dir)
{
	t_color	color;
	t_v3	l;
	t_v3	r;
	t_light	*light;
	double	d;
	double	s;
	int		shadowed;

	color = phong_ambiant(&scene->ambiant.color, &intersect->obj->mat.reflection_ratio);
	while (lights)
	{
		light = lights->content;
		l = v_direction_to(intersect->point, (light->origin));
		shadowed = in_shadow(scene, intersect, light);
		d = v_dot(l, intersect->normal);
		if (!shadowed && d > 0)
		{
			color = color_add_normalized(color, phong_diffuse(&light->color,
						&intersect->obj->mat.reflection_ratio, d));
			r = v_add(v_scalarmul(intersect->normal, 2 * v_dot(l, intersect->normal)), v_scalarmul(l, -1));
			s = v_dot(r, view_dir);
			if (s > 0)
			{
				color = color_add_bounded(color, phong_specular(&light->color,
							intersect->obj->mat.specular_ratio, pow(s, intersect->obj->mat.shininess)));
			}
		}
		lights = lights->next;
	}
	return (color);
}

static t_color	compute_color(t_scene const *scene, t_ray const *ray){
	t_color	color;
	t_intersect	intersect;

	if (compute_closest_intersect(scene, ray, &intersect) >= 0)
	{
//		printf("closest intersect: "); obj_print(intersect.obj); printf("\n");
		color = compute_phong(scene, scene->lights, &intersect, v_scalarmul(ray->dir, -1));
	}
	else{
//		printf("no intersect\n");
		color = scene->background;
	}
	return (color);
}

void	compute_scene(t_scene const *scene, t_img *img)
{
	t_ray	ray;
	t_color	p_color;
	int		i;
	int		j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			ray = cam_pixel_to_ray(&scene->cam, i, j);
//			ray_print(&ray);printf("\n");
			p_color = compute_color(scene, &ray);
			img_set_pixel(img, i, j, p_color);
			++i;
		}
		++j;
	}
}
