/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 15:59:23 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/01/30 12:15:44 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_XYZ	vector(double x, double y, double z)
{
	t_XYZ	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_XYZ	vec_subtract(t_XYZ *v1, t_XYZ *v2)
{
	t_XYZ	dst;

	dst.x = v1->x - v2->x;
	dst.y = v1->y - v2->y;
	dst.z = v1->z - v2->z;
	return (dst);
}

int	same_point(t_XYZ *p1, t_XYZ *p2)
{
	return (p1->x == p2->x && p1->y == p2->y && p1->z == p2->z);
}

double	veclen(t_XYZ *vec)
{
	return (sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2)));
}

t_XYZ	cross_prod(t_XYZ *v1, t_XYZ *v2)
{
	t_XYZ	dst;

	dst.x = v1->y * v2->z - v1->z * v2->y;
	dst.y = v1->z * v2->x - v1->x * v2->z;
	dst.z = v1->x * v2->y - v1->y * v2->x;
	return (dst);
}

double	dot_prod(t_XYZ *p1, t_XYZ *p2)
{
	return (p1->x * p2->x + p1->y * p2->y + p1->z * p2->z);
}

double	distance(t_XYZ *p1, t_XYZ *p2)
{
	return (sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2) + pow(p1->z
				- p2->z, 2)));
}

double	distancetoline(t_XYZ *p, t_XYZ *linepoint, t_XYZ *dir)
{
	t_XYZ	tmp;
	t_XYZ	nominator;

	tmp = vec_subtract(p, linepoint);
	nominator = cross_prod(&tmp, dir);
	return (veclen(&nominator) / veclen(dir));
}

t_XYZ	*normalize(t_XYZ *vec)
{
	float	norm;
	float	len;

	len = veclen(vec);
	if (len != 1)
	{
		norm = 1 / len;
		vec->x *= norm;
		vec->y *= norm;
		vec->z *= norm;
	}
	return (vec);
}
