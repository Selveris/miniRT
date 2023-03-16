#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "miniRT.h"

static t_ses	*create_session(void *mlx, void *win)
{
	t_ses	*ses;

	if (!mlx || !win)
		return (NULL);
	ses = ft_calloc(1, sizeof(t_ses));
	if (!ses)
		return (NULL);
	ses->mlx = mlx;
	ses->win = win;
	return (ses);
}

t_ses	*start_session(void)
{
	void	*mlx;
	void	*win;
	t_ses	*ses;

	mlx = mlx_init();
	win = NULL;
	if (mlx)
		win = mlx_new_window(mlx, WIN_W, WIN_H, WIN_NAME);
	ses = create_session(mlx, win);
	if (!win || !mlx || !ses)
	{
		ft_putstr_fd("Error\nSession creation failed\n", 2);
		return (NULL);
	}
	mlx_hook(ses->win, DESTROY_NOTIFY, 0, close_session, ses);
	mlx_key_hook(ses->win, key_hook, ses);
	mlx_loop_hook(ses->mlx, loop_hook, ses);
	return (ses);
}

int	close_session(t_ses *ses)
{
	if (!ses)
		return (1);
	mlx_destroy_window(ses->mlx, ses->win);
	free(ses);
	exit(EXIT_SUCCESS);
}

int	key_hook(int key, t_ses *ses)
{
	if (key == 53)
		close_session(ses);
	return (0);
}

int	loop_hook(t_ses *ses)
{
	(void) ses;
	return (0);
}
