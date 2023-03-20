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
	if (m_intersect->obj){
		m_intersect->viewer = v_scalarmul(ray->dir, -1);
		return (m_dist);
	}
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
	ray.origin = v_add(intersect->point, v_scalarmul(intersect->normal, O_MIN_DIST));
	ray.dir = v_direction_to(intersect->point, light->origin);
	m_dist = compute_closest_intersect(scene, &ray, &m_intersect);
	if (m_dist >= 0 && m_dist < l_dist)
		return (1);
	return (0);
}

static void	compute_lights(t_color *color, t_scene const *scene,
		t_intersect const *intersect)
{
	t_list	*lights;
	t_v3	v;
	t_light	*light;
	double	d;

	lights = scene->lights;
	while (lights)
	{
		light = lights->content;
		v = v_direction_to(intersect->point, light->origin);
		d = v_dot(v, intersect->normal);
		if (d > 0 && !in_shadow(scene, intersect, light))
		{
			color_add_normalized(color, color_smul(color_vmul(light->color,
							&intersect->obj->mat.diffuse_ratio), d));
			v = v_symmetric(v, intersect->normal);
			d = v_dot(v, intersect->viewer);
			if (d > 0)
			{
				color_add_bounded(color, color_smul(light->color, pow(d,
					intersect->obj->mat.shininess) * intersect->obj->mat.specular_ratio));
			}
		}
		lights = lights->next;
	}
}

static t_color	compute_color(t_scene const *scene, t_ray const *ray, int depth){
	t_color		color;
	t_intersect	intersect;
	t_ray		r_ray;

	if (depth > RAY_MAX_DEPTH)
		return C_BLACK;
	if (compute_closest_intersect(scene, ray, &intersect) >= 0)
	{
		r_ray.origin = v_add(intersect.point, v_scalarmul(intersect.normal, O_MIN_DIST));
		r_ray.dir = v_symmetric(intersect.viewer, intersect.normal);
		color = color_vmul(scene->ambiant.color, &intersect.obj->mat.diffuse_ratio);
		color_add_normalized(&color, color_smul(compute_color(scene, &r_ray, depth + 1), intersect.obj->mat.reflection_ratio));
		compute_lights(&color, scene, &intersect);
	}
	else{
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
			p_color = compute_color(scene, &ray, 0);
			img_set_pixel(img, i, j, p_color);
			++i;
		}
		++j;
	}
}
