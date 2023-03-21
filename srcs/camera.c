#include <math.h>
#include "miniRT.h"

#include <stdio.h>

void	init_cam_dir(t_cam *cam, t_v3 const dir)
{
	cam->yaw = atan2(-dir.x, -dir.z);
	cam->pitch = atan2(dir.y, sqrt(dir.x * dir.x + dir.z * dir.z));
	cam->roll = 0;
}

static t_v3	cam_to_world(t_cam const *cam, t_v3 const v)
{
	t_v3	new;

	new.x = cos(cam->yaw)*cos(cam->roll)*v.x
			+ (sin(cam->pitch)*sin(cam->yaw)*cos(cam->roll) 
				- cos(cam->pitch)*sin(cam->roll))*v.y
			+ (cos(cam->pitch)*sin(cam->yaw)*cos(cam->roll) 
				+ sin(cam->pitch)*sin(cam->roll))*v.z;
	new.y = cos(cam->yaw)*sin(cam->roll)*v.x 
			+ (sin(cam->pitch)*sin(cam->yaw)*sin(cam->roll) 
				+ cos(cam->pitch)*cos(cam->roll))*v.y
			+ (cos(cam->pitch)*sin(cam->yaw)*sin(cam->roll)
				- sin(cam->pitch)*cos(cam->roll))*v.z;
	new.z = -sin(cam->yaw)*v.x + sin(cam->pitch)*cos(cam->yaw)*v.y 
			+ cos(cam->pitch)*cos(cam->yaw)*v.z;
	return (new);
}
/*t_ray	cam_pixel_to_ray(t_cam const *cam, int i, int j){
	t_v3	p;
	t_ray	ray;

	p.x = i - WIN_W / 2;
	if (!(WIN_W % 2))
		p.x += 0.5f;
	p.y = WIN_H / 2 - j;
	if (!(WIN_H % 2))
		p.y -= 0.5f;
	if (cam->fov == 180)
		p.z = 0;
	else if (cam->fov == 0)
		p.z = -WIN_W / (2 * tan(0.001f));
	else
		p.z = -WIN_W / (2 * tan(cam->fov / 2.0f));
	ray.origin = cam->origin;
	ray.dir = cam_to_world(cam, v_normalize(p));
	return (ray);
}*/
static t_v3	cam_pixel_vector(t_cam const *cam, int i, int j, int a)
{
	t_v3	p;

	p.x = i - WIN_W / 2.0 + (a % ALIASING + 0.5) / ALIASING;
	p.y = WIN_H / 2.0 - j - (a / ALIASING + 0.5) / ALIASING;
	if (cam->fov == 180)
		p.z = 0;
	else if (cam->fov == 0)
		p.z = -WIN_W / (2 * tan(0.001f));
	else
		p.z = -WIN_W / (2 * tan(cam->fov / 2.0f));
	return (cam_to_world(cam, v_normalize(p)));
}
void	cam_pixel_to_rays(t_ray *rays, t_cam const *cam, int i, int j){
	int		a;

	a = 0;
	while (a < ALIASING * ALIASING)
	{
		rays[a].origin = cam->origin;
		rays[a].dir = cam_pixel_vector(cam, i, j, a);
		++a;
	}
}

