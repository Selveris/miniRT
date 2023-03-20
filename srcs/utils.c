#include <math.h>
#include "miniRT.h"

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	solve_quadratic(double a, double b, double c)
{
	double d;
	double x0;
	double x1;

	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	if (d == 0)
		return (-b / (2 * a));
	if (b > 0)
		d = -0.5 * (b + sqrt(d));
	else
		d = -0.5 * (b - sqrt(d));
	x0 = d / a;
	x1 = c / d;
	if (x0 > x1)
	{
		d = x0;
		x0 = x1;
		x1 = d;
	}
	if (x0 >= 0)
		return (x0);
	else
		return (x1);
}
