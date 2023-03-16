#include <mlx.h>
#include <libft.h>
#include <stdlib.h>
#include <math.h>
#include "miniRT.h"

#include <stdio.h>

void	test(t_ses *ses)
{
	(void) ses;
	t_cam	cam;
	t_v3	dir;
	dir.x = -1;
	dir.y = 0;
	dir.z = 0;
	cam.origin = V_ZERO;
	cam.fov = 140;
	init_cam_dir(&cam, v_normalize(dir));
	printf("%f | %f | %f\n", cam.yaw/M_PI * 180, cam.pitch/M_PI * 180, cam.roll);
	t_ray	ray = cam_pixel_to_ray(&cam, WIN_W/2, 0);
	printf("%f | %f | %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
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
