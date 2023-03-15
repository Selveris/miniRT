#ifndef MINIRT_H
# define MINIRT_H
# include <OpenGL/gl3.h>

//---------------------------------//
//             config              //
//---------------------------------//
# define WIN_NAME		"So long"
# define WIN_W			960
# define WIN_H			540
# define DESTROY_NOTIFY	17

typedef struct s_session
{
	void	*mlx;
	void	*win;
}	t_ses;

t_ses	*start_session(void);
int		close_session(t_ses *ses);
int		key_hook(int key, t_ses *ses);
int		loop_hook(t_ses *ses);

#endif
