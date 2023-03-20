#include <stddef.h>
#include "miniRT.h"

double	plane_intersect(t_ray const *ray, t_obj const *obj,
						t_intersect *intersect)
{
	double			angle;
	double			dist;
	t_plane const	*plane;

	plane = &obj->geometry.plane;
	angle = v_dot(plane->normal, ray->dir);
	if (angle)
		dist = -(v_dot(plane->normal, ray->origin) + plane->dist) / angle;
	if (angle == 0 || dist < 0)
	{
		intersect->obj = NULL;
		return (-1);
	}
	intersect->point = ray_forward(ray, dist);
	if (angle > 0)
		intersect->normal = v_scalarmul(plane->normal, -1);
	else
		intersect->normal = plane->normal;
	intersect->obj = obj;
	return (dist);
}

double	sphere_intersect(t_ray const *ray, t_obj const *obj,
		t_intersect *intersect)
{
	t_v3			cp;
	t_v3			co;
	double			dist;
	t_sphere const	*sphere;

	sphere = &obj->geometry.sphere;
	co = v_add(v_scalarmul(sphere->origin, -1), ray->origin);
	dist = solve_quadratic(1, 2 * v_dot(ray->dir, co),
			v_dot(co, co) - sphere->r * sphere->r);
	if (dist < 0)
	{
		intersect->obj = NULL;
		return (-1);
	}
	intersect->point = ray_forward(ray, dist);
	intersect->obj = obj;
	cp = v_direction_to(sphere->origin, intersect->point);
	if (v_norm(co) <= sphere->r)
		intersect->normal = v_scalarmul(cp, -1);
	else
		intersect->normal = cp;
	return (dist);
}
