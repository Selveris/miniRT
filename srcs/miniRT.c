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

	scene.objs = NULL;
	scene.lights = NULL;

	dir = (t_v3) {0, 0, -1};
	scene.cam.origin = V_ZERO;
	scene.cam.origin.y = 1;
	scene.cam.fov = 140;
	init_cam_dir(&scene.cam, v_normalize(dir));
	scene.background = C_BLACK;
	double	ai = 0.1;
	scene.ambiant.color = (t_color) {255 * ai, 255 * ai, 255 * ai};

	t_obj	plane;
	plane.type = O_PLANE;
	plane.geometry.plane.normal = (t_v3) {0, 1, 0};
	plane.geometry.plane.dist = 0;
	t_v3	plane_color = (t_v3) {220, 220, 220};
	plane.mat.diffuse_ratio = v_scalarmul(plane_color, 1.0/255);
	plane.mat.specular_ratio = 0.2;
	plane.mat.shininess = 1;
	plane.mat.reflection_ratio = 0;
	ft_lstadd_back(&scene.objs, ft_lstnew(&plane));
	t_obj	plane2;
	plane2.type = O_PLANE;
	plane2.geometry.plane.normal = (t_v3) {0, 0, 1};
	plane2.geometry.plane.dist = 10;
	t_v3	plane2_color = (t_v3) {0, 0, 0};
	plane2.mat.diffuse_ratio = v_scalarmul(plane2_color, 1.0/255);
	plane2.mat.specular_ratio = 0;
	plane2.mat.shininess = 32;
	plane2.mat.reflection_ratio = 1;
	ft_lstadd_back(&scene.objs, ft_lstnew(&plane2));
	t_obj	plane3;
	plane3.type = O_PLANE;
	plane3.geometry.plane.normal = (t_v3) {0, 0, 1};
	plane3.geometry.plane.dist = -2;
	t_v3	plane3_color = (t_v3) {0, 0, 0};
	plane3.mat.diffuse_ratio = v_scalarmul(plane3_color, 1.0/255);
	plane3.mat.specular_ratio = 0;
	plane3.mat.shininess = 32;
	plane3.mat.reflection_ratio = 1;
	ft_lstadd_back(&scene.objs, ft_lstnew(&plane3));
	t_obj	sphere;
	sphere.type = O_SPHERE;
	sphere.geometry.sphere.origin = (t_v3) {2.5, 2.5, -5.5};
	sphere.geometry.sphere.r = 1;
	t_v3	sphere_color = (t_v3) {200, 200, 200};
	sphere.mat.diffuse_ratio = v_scalarmul(sphere_color, 1.0/255);
	sphere.mat.specular_ratio = 0.4;
	sphere.mat.shininess = 32;
	sphere.mat.reflection_ratio = 0.1;
	ft_lstadd_back(&scene.objs, ft_lstnew(&sphere));

/*	t_light	light;
	light.origin = (t_v3) {1, 10, -3};
	light.color = C_RED;
	ft_lstadd_back(&scene.lights, ft_lstnew(&light));
	t_light	light2;
	light2.origin = (t_v3) {-1, 10, -3};
	light2.color = C_GREEN;
	ft_lstadd_back(&scene.lights, ft_lstnew(&light2));*/
	t_light	light3;
	light3.origin = (t_v3) {0, 10, -4};
	light3.color = C_WHITE;
	ft_lstadd_back(&scene.lights, ft_lstnew(&light3));
	
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
	return (EXIT_SUCCESS);
}
