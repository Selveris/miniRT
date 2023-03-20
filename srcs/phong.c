#include "miniRT.h"

t_color	color_add_normalized(t_color c1, t_color c2)
{
	double	r;
	double	red;
	double	green;
	double	blue;
	t_color	color;

	red = (double)c1.red + c2.red;
	green = (double)c1.green + c2.green;
	blue = (double)c1.blue + c2.blue;
	r = 255 / max(max(red, green), blue);
	if (r < 1)
		color = (t_color){red * r, green * r, blue * r};
	else
		color = (t_color){red, green, blue};
	return (color);
}

t_color	color_add_bounded(t_color c1, t_color c2)
{
	t_color	color;

	color.red = min(255, c1.red + c2.red);
	color.green = min(255, c1.green + c2.green);
	color.blue = min(255, c1.blue + c2.blue);
	return (color);
}

t_color	phong_ambiant(t_color const *ambiant, t_v3 const *ratio)
{
	t_color	color;

	color.red = ambiant->red * ratio->x;
	color.green = ambiant->green * ratio->y;
	color.blue = ambiant->blue * ratio->z;
	return (color);
}

t_color	phong_diffuse(t_color const *light, t_v3 const *ratio, double d)
{
	t_color	color;

	color.red = light->red * ratio->x * d;
	color.green = light->green * ratio->y * d;
	color.blue = light->blue * ratio->z * d;
	return (color);
}

t_color	phong_specular(t_color const *light, double ratio, double s)
{
	t_color color;

	color.red = light->red * s * ratio;
	color.green = light->green * s * ratio;
	color.blue = light->blue * s * ratio;
	return (color);
}
