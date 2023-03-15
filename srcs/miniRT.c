#include <mlx.h>
#include <libft.h>
#include <stdlib.h>
#include "miniRT.h"

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
	ft_printf("Exit\n");
	return (EXIT_SUCCESS);
}
