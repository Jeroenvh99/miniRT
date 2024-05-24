/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:33:23 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/20 16:01:42 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

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
	return (mag_vec(&nominator) / mag_vec(dir));
}

int	onLine(t_XYZ *point, t_ray *line)
{
	t_XYZ	tmp;
	double	nominator;

	tmp = vec_subtraction(*point, line->origin);
	nominator = (double)tmp.x / (double)line->dir.x;
	return ((double)tmp.y / (double)line->dir.y == nominator && (double)tmp.z / (double)line->dir.z == nominator);
}
