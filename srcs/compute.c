#include <math.h>
#include "miniRT.h"

static t_color	compute_pixel_color(t_scene const *scene, t_ray const *ray){

}

static t_ray	get_ray_for_pixel(t_cam *cam, int i, int j){
	t_v3	p;
	float	fov;

	fov = (float)cam->fov * WIN_H / WIN_W;
	p.x = i - WIN_W / 2;
	if (!(WIN_W % 2))
		p.x += 0.5f;
	p.y = WIN_H / 2 - j;
	if (!(WIN_H % 2))
		p.y -= 0.5f;
	p.z = -(WIN_H / 2) / tan(fov / 2);
}

void	*compute_scene(t_ses *ses)
{
	void	*scene;
	t_ray	ray;
	t_color	p_color;
	int		i;
	int		j;

	scene = mlx_new_image(ses->mlx, WIN_W, WIN_H);
	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			ray = get_ray_for_pixel(&ses->scene.cam, i, j);
			p_color = compute_pixel_color(ses->scene, &ray);
			img_set_pixel(scene, i, j, p_color);
			++i;
		}
		++j;
	}
}
