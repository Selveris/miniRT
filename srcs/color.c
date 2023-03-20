#include "miniRT.h"

void	color_add_normalized(t_color *base, t_color add)
{
	double	r;
	double	red;
	double	green;
	double	blue;

	red = (double)base->red + add.red;
	green = (double)base->green + add.green;
	blue = (double)base->blue + add.blue;
	r = 255 / max(max(red, green), blue);
	if (r < 1)
		*base = (t_color){red * r, green * r, blue * r};
	else
		*base = (t_color){red, green, blue};
}

void	color_add_bounded(t_color *base, t_color add)
{
	base->red = min(255, (int)base->red + add.red);
	base->green = min(255, (int)base->green + add.green);
	base->blue = min(255, (int)base->blue + add.blue);
}

t_color	color_vmul(t_color const base, t_v3 const *ratio)
{
	t_color color;

	color.red = base.red * ratio->x;
	color.green = base.green * ratio->y;
	color.blue = base.blue * ratio->z;
	return (color);
}

t_color	color_smul(t_color const base, double ratio)
{
	t_color	color;

	color.red = base.red * ratio;
	color.green = base.green * ratio;
	color.blue = base.blue * ratio;	
	return (color);
}
