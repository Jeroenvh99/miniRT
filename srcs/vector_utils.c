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

int	same_point(t_XYZ *p1, t_XYZ *p2)
{
	return (p1->x == p2->x && p1->y == p2->y && p1->z == p2->z);
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

	tmp = vec_subtraction(*p, *linepoint);
	nominator = cross_vec(tmp, *dir);
	return (mag_vec(nominator) / mag_vec(*dir));
}
