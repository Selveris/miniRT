#include <math.h>
#include "miniRT.h"

t_v3	v_normalize(t_v3 v)
{
	float	norm;
	t_v3	n;

	norm = v.x*v.x + v.y*v.y + v.z*v.z;
	n.x = v.x / sqrt(norm);
	n.y = v.y / sqrt(norm);
	n.z = v.z / sqrt(norm);
	return (n);
}
