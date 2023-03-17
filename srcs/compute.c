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

static t_color	compute_phong(t_ambiant const *ambiant, t_list const *lights, 
		t_intersect const *intersect)
{
	t_color	color;
	(void) lights;

	color.red = ambiant->strength * ambiant->color.red * intersect->obj->color.red / 255;
	color.green = ambiant->strength * ambiant->color.green * intersect->obj->color.green / 255;
	color.blue = ambiant->strength * ambiant->color.blue * intersect->obj->color.blue / 255;
	return (color);
}

static t_color	compute_color(t_scene const *scene, t_ray const *ray){
	t_color	color;
	t_intersect	intersect;

	intersect = compute_closest_intersect(scene, ray);
	if (intersect.obj)
	{
		color = compute_phong(&scene->ambiant, scene->lights, &intersect);
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
