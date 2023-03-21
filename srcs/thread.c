#include <pthread.h>
#include "miniRT.h"

#include <stdio.h>

void	thread_join_all(t_thread *threads)
{
	t_thread	*thread;
	int			i;

	i = 0;
	while (i < THREAD_C)
	{
		thread = threads + i;
		pthread_join(thread->pthread, NULL);
		thread->done = 0;
		thread->pthread = 0;
		++i;
	}
}

int	thread_all_done(t_thread *threads)
{
	int	i;

	i = 0;
	while (i < THREAD_C)
	{
		if (!threads[i].done)
			return (0);
		++i;
	}
	return (1);
}

static void	*thread_compute_scene(void *arg)
{
	t_thread	*thread;
	t_ray		ray;
	t_color		p_color;
	size_t		i;
	size_t		j;

	thread = arg;
	j = thread->j_from;
	i = thread->i_from;
	while (j < WIN_H && thread->p > 0)
	{
		while (i < WIN_W && thread->p > 0)
		{
			ray = cam_pixel_to_ray(&thread->scene->cam, i, j);
			p_color = compute_color(thread->scene, &ray, 0);
			img_set_pixel(thread->img, i, j, p_color);
			++i;
			--thread->p;
		}
		i = 0;
		++j;
	}
	thread->done = 1;
	return (NULL);
}

void	thread_start_compute(t_thread *threads, t_scene *scene, t_img *img)
{
	size_t		i;
	size_t		p;
	size_t		s;
	t_thread	*thread;

	p = WIN_W * WIN_H / THREAD_C;
	i = 0;
	while (i < THREAD_C)
	{
		s = i * p;
		thread = threads + i;
		thread->scene = scene;
		thread->img = img;
		thread->done = 0;
		thread->j_from = s / WIN_W;
		thread->i_from = s % WIN_W;
		thread->p = p;
		if (i == THREAD_C - 1)
			thread->p += (WIN_W * WIN_H) % THREAD_C;
		pthread_create(&thread->pthread, NULL, &thread_compute_scene, thread);
		++i;
	}
}
