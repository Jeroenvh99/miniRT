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

t_XYZ	vec_multiplication(double factor, t_XYZ vector)
{
	t_XYZ	res;

	res.x = factor * vector.x;
	res.y = factor * vector.y;
	res.z = factor * vector.z;
	return (res);
}

t_XYZ	vec_addition(t_XYZ vec1, t_XYZ vec2)
{
	t_XYZ	res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

t_XYZ	vec_subtraction(t_XYZ vec1, t_XYZ vec2)
{
	t_XYZ	res;

	res.x = vec1.x - vec2.x;
	res.y = vec1.y - vec2.y;
	res.z = vec1.z - vec2.z;
	return (res);
}
