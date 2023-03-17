#include <mlx.h>
#include <libft.h>
#include <stdlib.h>
#include <math.h>
#include "miniRT.h"

#include <stdio.h>

void	test(t_ses *ses)
{
	t_scene	scene;
	t_v3	dir;
	t_img	*window;

	dir.x = 0;
	dir.y = 0;
	dir.z = -1;
	scene.cam.origin = V_ZERO;
	scene.cam.origin.y = 1;
	scene.cam.fov = 140;
	init_cam_dir(&scene.cam, v_normalize(dir));

	t_obj	plane;
	plane.type = O_PLANE;
	plane.data.plane.normal.x = 0;
	plane.data.plane.normal.y = 1;
	plane.data.plane.normal.z = 0;
	plane.data.plane.dist = 0;
	plane.color.red = 50;
	plane.color.green = 200;
	plane.color.blue = 50;
	scene.objs = ft_lstnew(&plane);
	
	window = img_create(ses->mlx, WIN_W, WIN_H);
	compute_scene(&scene, window);
	mlx_put_image_to_window(ses->mlx, ses->win, window->mlx_img, 0, 0);
	img_destroy(ses->mlx, &window);
}

int	main(int argc, char **argv)
{
	t_ses	*ses;

	(void) argc;
	(void) argv;
	
	ses = start_session();
	if (!ses)
		return (EXIT_FAILURE);
	test(ses);
	mlx_loop(ses->mlx);
	free(ses);
	ft_printf("Exit\n");
	return (EXIT_SUCCESS);
}
