#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "miniRT.h"

void	img_set_pixel(t_img *img, int i, int j, t_color color)
{
	int	offset;

	offset = img->l_size * j + i * (img->bpp / 8);
	img->data[offset] = color.blue;
	img->data[offset + 1] = color.green;
	img->data[offset + 2] = color.red;
}

t_img	*img_create(void *mlx, int width, int height)
{
	void	*mlx_img;
	t_img	*img;

	if (!mlx || width <= 0 || height <= 0)
		return (NULL);
	img = ft_calloc(1, sizeof(t_img));
	mlx_img = mlx_new_image(mlx, width, height);
	if (!img || !mlx_img)
	{
		free(img);
		mlx_destroy_image(mlx, mlx_img);
		return (NULL);
	}
	img->mlx_img = mlx_img;
	img->data = (unsigned char *)mlx_get_data_addr(mlx_img, &img->bpp,
					&img->l_size, &img->endian);
	return (img);
}

void	img_destroy(void *mlx, t_img **img)
{
	if (!mlx || !img || !*img)
		return ;
	mlx_destroy_image(mlx, (*img)->mlx_img);
	free(*img);
	*img = NULL;
}
