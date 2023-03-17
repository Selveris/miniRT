#include <math.h>
#include "miniRT.h"

t_v3	v_cross(t_v3 a, t_v3 b)
{
	t_v3	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

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

t_v3	v_reverse(t_v3 v)
{
	t_v3	rev;

	rev.x = -v.x;
	rev.y = -v.y;
	rev.z = -v.z;
	return (rev);
}

t_v3	ray_forward(t_ray const *ray, double dist)
{
	t_v3	point;

	point.x = ray->origin.x + ray->dir.x * dist;
	point.y = ray->origin.y + ray->dir.y * dist;
	point.z = ray->origin.z + ray->dir.z * dist;
	return (point);
}
