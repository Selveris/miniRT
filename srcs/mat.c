#include <math.h>
#include "miniRT.h"

t_mat	create_mat(t_color color, unsigned int shininess, double reflection)
{
	t_mat	mat;

	mat.diffuse_ratio = (t_v3){color.red / 255.0, color.green / 255.0,
		color.blue / 255.0};
	mat.reflection_ratio = reflection;
	mat.shininess = shininess;
	mat.specular_ratio = 1 - 1 / (log10(0.2 * shininess + 10));
	return (mat);
}
