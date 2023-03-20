#include "miniRT.h"

#include <stdio.h>

void	v3_print(t_v3 const *v)
{
	printf("(%f, %f, %f)", v->x, v->y, v->z);
}

void	ray_print(t_ray const *ray)
{
	printf("ray[");
	v3_print(&ray->origin);
	printf(" -> ");
	v3_print(&ray->dir);
	printf("]");
}

void	obj_print(t_obj const *obj)
{
	printf("%p\n", obj);
	printf("%p, %f\n", &obj->geometry.plane.normal, obj->geometry.plane.dist);
	switch(obj->type)
	{
		case O_PLANE:
			printf("plane");
			printf("[n = ");
			v3_print(&obj->geometry.plane.normal);
			printf(", d = %f]", obj->geometry.plane.dist);
			break;
		default:
			printf("Unknown object");
			return;
	}
}
