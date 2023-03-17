#include <math.h>
#include <float.h>
#include "miniRT.h"

#include <stdio.h>

static t_intersect	compute_closest_intersect(t_scene const *scene,
		t_ray const *ray)
{
	t_list		*objs;
	t_intersect	m_intersect;
	double		m_dist;
	t_intersect	intersect;
	double		dist;

	m_intersect.obj = NULL;
	m_dist = DBL_MAX;
	objs = scene->objs;
	while (objs)
	{
		dist = obj_intersect[((t_obj *)objs->content)->type](ray,
					objs->content, &intersect);
		if (dist < m_dist)
		{
			m_dist = dist;
			m_intersect = intersect;
		}
		objs = objs->next;	
	}
	return (m_intersect);
}

static t_color	compute_phong(t_ambiant const *ambiant, t_list *lights, 
		t_intersect const *intersect, t_v3 view_dir)
{
	t_color	color;
	t_v3	l;
	t_v3	r;
	t_light	*light;
	double	d;
	double	s;

	color.red = ambiant->color.red * intersect->obj->mat.reflection_ratio.x;
	color.green = ambiant->color.green * intersect->obj->mat.reflection_ratio.y;
	color.blue = ambiant->color.blue * intersect->obj->mat.reflection_ratio.z;
	while (lights)
	{
		light = lights->content;
		l = v_direction_to(intersect->point, (light->origin));
		d = v_dot(l, intersect->normal);
		if (d > 0)
		{
			color.red += intersect->obj->mat.reflection_ratio.x * d * light->color.red;
			color.green += intersect->obj->mat.reflection_ratio.y * d * light->color.green;
			color.blue += intersect->obj->mat.reflection_ratio.z * d * light->color.blue;
			r = v_add(v_scalarmul(intersect->normal, 2 * v_dot(l, intersect->normal)), v_scalarmul(l, -1));
			s = v_dot(r, view_dir);
			if (s > 0)
			{
				s = intersect->obj->mat.specular_ratio * pow(s, intersect->obj->mat.shininess);
				color.red += s * light->color.red;
				color.green += s * light->color.green;
				color.blue += s * light->color.blue;
			}
		}
		lights = lights->next;
	}
	return (color);
}

static t_color	compute_color(t_scene const *scene, t_ray const *ray){
	t_color	color;
	t_intersect	intersect;

	intersect = compute_closest_intersect(scene, ray);
	if (intersect.obj)
	{
		color = compute_phong(&scene->ambiant, scene->lights, &intersect, v_scalarmul(ray->dir, -1));
	}
	else
		color = scene->background;
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
			p_color = compute_color(scene, &ray);
			img_set_pixel(img, i, j, p_color);
			++i;
		}
		++j;
	}
}
