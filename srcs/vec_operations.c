/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:33:23 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/21 15:02:52 by sjeddi           ###   ########.fr       */
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

double	dot_vec(t_XYZ vec1, t_XYZ vec2)
{
	double	res;

	res = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (res);
}

t_XYZ	cross_vec(t_XYZ vec1, t_XYZ vec2)
{
	t_XYZ	res;

	res.x = vec1.y * vec2.z - vec1.z * vec2.y;
	res.y = vec1.z * vec2.x - vec1.x * vec2.z;
	res.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (res);
}

double	mag_vec(t_XYZ *vector)
{
	double	res;

	res = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	return (res);
}

void	norm_vec(t_XYZ *vector)
{
	double	mag;

	mag = mag_vec(vector);
	vector->x /= mag;
	vector->y /= mag;
	vector->z /= mag;
}

t_XYZ	vec_packer(double x, double y, double z)
{
	t_XYZ	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}