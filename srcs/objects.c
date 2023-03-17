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
		intersect->normal = v_reverse(plane->normal);
	else
		intersect->normal = plane->normal;
	intersect->obj = obj;
	return (dist);
}
