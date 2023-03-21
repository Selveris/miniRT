#include <mlx.h>
#include <libft.h>
#include <stdlib.h>
#include <math.h>
#include "miniRT.h"

#include <stdio.h>
#include <unistd.h>

void	*load_scene(void *arg)
{
	t_scene	*scene;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->objs = NULL;
	scene->lights = NULL;
	
	t_v3	dir;
	dir = (t_v3) {0, 0, -1};
	scene->cam.origin = (t_v3){0, 1, -0.1};
	scene->cam.fov = 140;
	init_cam_dir(&scene->cam, v_normalize(dir));
	scene->background = C_BLACK;
	double	ai = 0.1;
	scene->ambiant.color = (t_color) {255 * ai, 255 * ai, 255 * ai};

	t_obj	*plane = ft_calloc(1, sizeof(t_obj));
	plane->type = O_PLANE;
	plane->geometry.plane.normal = (t_v3) {0, 1, 0};
	plane->geometry.plane.dist = 0;
	t_v3	plane_color = (t_v3) {220, 220, 220};
	plane->mat.diffuse_ratio = v_scalarmul(plane_color, 1.0/255);
	plane->mat.specular_ratio = 0.2;
	plane->mat.shininess = 1;
	plane->mat.reflection_ratio = 0;
	ft_lstadd_back(&scene->objs, ft_lstnew(plane));
	t_obj	*plane2 = ft_calloc(1, sizeof(t_obj));
	plane2->type = O_PLANE;
	plane2->geometry.plane.normal = (t_v3) {0, 0, 1};
	plane2->geometry.plane.dist = 10;
	t_v3	plane2_color = (t_v3) {0, 80, 150};
	plane2->mat.diffuse_ratio = v_scalarmul(plane2_color, 1.0/255);
	plane2->mat.specular_ratio = 0;
	plane2->mat.shininess = 32;
	plane2->mat.reflection_ratio = 0.8;
	ft_lstadd_back(&scene->objs, ft_lstnew(plane2));
	t_obj	*plane3 = ft_calloc(1, sizeof(t_obj));
	plane3->type = O_PLANE;
	t_v3	plane3_n = (t_v3) {-1, 0, -1};
	plane3_n = v_normalize(plane3_n);
	plane3->geometry.plane.normal = plane3_n;
	plane3->geometry.plane.dist = 0;
	t_v3	plane3_color = (t_v3) {0, 0, 0};
	plane3->mat.diffuse_ratio = v_scalarmul(plane3_color, 1.0/255);
	plane3->mat.specular_ratio = 0;
	plane3->mat.shininess = 32;
	plane3->mat.reflection_ratio = 1;
	ft_lstadd_back(&scene->objs, ft_lstnew(plane3));
	t_obj	*plane4 = ft_calloc(1, sizeof(t_obj));
	plane4->type = O_PLANE;
	t_v3	plane4_n = (t_v3) {1, 0, -1};
	plane4_n = v_normalize(plane4_n);
	plane4->geometry.plane.normal = plane4_n;
	plane4->geometry.plane.dist = 0;
	t_v3	plane4_color = (t_v3) {0, 0, 0};
	plane4->mat.diffuse_ratio = v_scalarmul(plane4_color, 1.0/255);
	plane4->mat.specular_ratio = 0;
	plane4->mat.shininess = 32;
	plane4->mat.reflection_ratio = 1;
	ft_lstadd_back(&scene->objs, ft_lstnew(plane4));
	t_obj	*sphere = ft_calloc(1, sizeof(t_obj));
	sphere->type = O_SPHERE;
	sphere->geometry.sphere.origin = (t_v3) {0, 2.5, -5.5};
	sphere->geometry.sphere.r = 1;
	t_v3	sphere_color = (t_v3) {200, 200, 200};
	sphere->mat.diffuse_ratio = v_scalarmul(sphere_color, 1.0/255);
	sphere->mat.specular_ratio = 0.4;
	sphere->mat.shininess = 32;
	sphere->mat.reflection_ratio = 0.05;
	ft_lstadd_back(&scene->objs, ft_lstnew(sphere));

	t_light	*light = ft_calloc(1, sizeof(t_light));
	light->origin = (t_v3) {1, 10, -3};
	light->color = C_RED;
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
	t_light	*light2 = ft_calloc(1, sizeof(t_light));
	light2->origin = (t_v3) {-1, 10, -3};
	light2->color = C_GREEN;
	ft_lstadd_back(&scene->lights, ft_lstnew(light2));
	t_light	*light3 = ft_calloc(1, sizeof(t_light));
	light3->origin = (t_v3) {0, 10, -4};
	light3->color = C_BLUE;
	ft_lstadd_back(&scene->lights, ft_lstnew(light3));


	sleep(1);

	t_ses	*ses = arg;
	ses->scene = scene;
	ses->img = img_create(ses->mlx, WIN_W, WIN_H);
	ses->threads->done = 1;

	return (scene);
}

int	loop_hook(t_ses *ses)
{
	mlx_clear_window(ses->mlx, ses->win);
	if (ses->loading){
		if (!ses->threads->pthread)
		{
			printf("Starting loading thread\n");
			pthread_create(&ses->threads->pthread, NULL, &load_scene, ses);
		}
		else if (!ses->threads->done)
		{
			mlx_string_put(ses->mlx, ses->win, WIN_W / 3, WIN_H / 2, (255 << 16) + (255 << 8) + 255, "Loading Scene");
		}
		else
		{
			printf("Loading Done!\n");
			pthread_join(ses->threads->pthread, NULL);
			ses->threads->pthread = 0;
			ses->threads->done = 0;
			ses->loading = 0;
			ses->computing = 1;
		}
	}
	else if (ses->computing){
		if (!ses->threads->pthread)
		{
			printf("Starting computing threads\n");
			thread_start_compute(ses->threads, ses->scene, ses->img);
		}
		else if (!thread_all_done(ses->threads))
		{
			mlx_string_put(ses->mlx, ses->win, WIN_W / 3, WIN_H / 2, (255 << 16) + (255 << 8) + 255, "Computing Scene");
		}
		else
		{
			printf("Computing Done!\n");
			thread_join_all(ses->threads);
			ses->computing = 0;
		}	
	}
	else
		mlx_put_image_to_window(ses->mlx, ses->win, ses->img->mlx_img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_ses	*ses;

	(void) argc;
	(void) argv;
	
	ses = start_session();
	if (!ses)
		return (EXIT_FAILURE);
	mlx_loop(ses->mlx);
	free(ses);
	return (EXIT_SUCCESS);
}
