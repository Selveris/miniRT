#include <pthread.h>
#include "miniRT.h"

#include <stdio.h>

int	thread_percent(t_thread *threads)
{
	int	p;
	int	i;

	i = 0;
	p = 0;
	while (i < THREAD_C)
	{
		p += threads[i].done;
		++i;
	}
	p /= THREAD_C;
	return (p);
}

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
		if (!(threads[i].done / 100))
			return (0);
		++i;
	}
	return (1);
}

static void	*thread_compute_scene(void *arg)
{
	t_thread	*thread;
	t_ray		rays[ALIASING * ALIASING];
	t_color		p_color[ALIASING * ALIASING];
	int			a;
	size_t		t;

	thread = arg;
	t = thread->p;
	while (thread->j < WIN_H && thread->p > 0)
	{
		while (thread->i < WIN_W && thread->p > 0)
		{
			a = 0;
			cam_pixel_to_rays(rays, &thread->scene->cam, thread->i, thread->j);
			while (a < ALIASING * ALIASING)
			{
				p_color[a] = compute_color(thread->scene, rays + a, 0);
				++a;
			}
			img_set_pixel(thread->img, thread->i, thread->j, color_average(p_color, ALIASING * ALIASING));
			++thread->i;
			--thread->p;
			thread->done = 100 - (thread->p * 100 / t);
		}
		thread->i = 0;
		++thread->j;
	}
	thread->done = 100;
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
		thread->j = s / WIN_W;
		thread->i = s % WIN_W;
		thread->p = p;
		if (i == THREAD_C - 1)
			thread->p += (WIN_W * WIN_H) % THREAD_C;
		pthread_create(&thread->pthread, NULL, &thread_compute_scene, thread);
		++i;
	}
}
