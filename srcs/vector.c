#include <math.h>
#include "miniRT.h"

double	v_dot(t_v3 a, t_v3 b)
{
	return (a.x * b.x + a.y*b.y + a.z*b.z);
}

t_v3	v_normalize(t_v3 v)
{
	float	norm;
	t_v3	n;

	norm = v.x*v.x + v.y*v.y + v.z*v.z;
	n.x = v.x / sqrt(norm);
	n.y = v.y / sqrt(norm);
	n.z = v.z / sqrt(norm);
	return (n);
}

t_v3	v_add(t_v3 a, t_v3 b)
{
	t_v3	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_v3	v_scalarmul(t_v3 v, double s)
{
	t_v3	new;

	new.x = v.x * s;
	new.y = v.y * s;
	new.z = v.z * s;
	return (new);
}

t_v3	v_direction_to(t_v3 origin, t_v3 dest)
{
	return (v_normalize(v_add(v_scalarmul(origin, -1), dest)));
}

t_v3	ray_forward(t_ray const *ray, double dist)
{
	t_v3	point;

	point.x = ray->origin.x + ray->dir.x * dist;
	point.y = ray->origin.y + ray->dir.y * dist;
	point.z = ray->origin.z + ray->dir.z * dist;
	return (point);
}
