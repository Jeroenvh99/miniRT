/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:48:19 by sjeddi            #+#    #+#             */
/*   Updated: 2024/07/25 15:35:17 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <stdio.h>

void	default_matrix(t_rt *rt)
{
	t_XYZ	ahead;
	t_XYZ	right;
	t_XYZ	up;
	t_XYZ	holder;
	t_XYZ	temp;

	holder = vector(0, 1, 0);
	ahead = rt->scene->cam.viewdirection;
	// norm_vec(&ahead);
	right = cross_vec(holder, ahead);
	up = cross_vec(ahead, right);
	temp = vector(0.2, 0, 0);
	right = vec_multiplication(0.8, right);
	rt->camtransform[0][0] = right.x;
	rt->camtransform[0][1] = right.y;
	rt->camtransform[0][2] = right.z;
	rt->camtransform[1][0] = up.x;
	rt->camtransform[1][1] = up.y;
	rt->camtransform[1][2] = up.z;
	rt->camtransform[2][0] = ahead.x;
	rt->camtransform[2][1] = ahead.y;
	rt->camtransform[2][2] = ahead.z;
}

// static void	print_XYZ(int fd, t_XYZ *pos)
// {
// 	dprintf(fd, "%f,%f,%f\n", pos->x, pos->y, pos->z);
// }

t_XYZ	base_transform(double matrix[3][3], t_XYZ dir)
{
	t_XYZ	res;

	res.x = dir.x * matrix[0][0] + dir.y * matrix[0][1] + dir.z * matrix[0][2];
	res.y = dir.x * matrix[1][0] + dir.y * matrix[1][1] + dir.z * matrix[1][2];
	res.z = dir.x * matrix[2][0] + dir.y * matrix[2][1] + dir.z * matrix[2][2];

	// for (int i = 0; i < 3; i++)
	// {
	// 	for (int j = 0; j < 3; j++)
	// 		printf("%f ", matrix[j][i]);
	// 	printf("\n");
	// }


	return (res);
}

t_ray	ray_launcher(t_rt *rt, t_ray ray, double x, double y)
{
	double scale;

	scale = tan((double)rt->scene->cam.fov * 0.5 * M_PI / 180);
	ray.origin = rt->scene->cam.pos;
	ray.dir.x = (2.0 * (x + 0.5) / (double)rt->width - 1.0) * scale
		* rt->aspectratio;
	ray.dir.y = (1.0 - 2.0 * (y + 0.5) / (double)rt->height) * scale;
	ray.dir.z = 1.0;
	norm_vec(&ray.dir);
	// print_XYZ(1, &ray.dir);
	// ray.dir = base_transform(rt->camtransform, ray.dir);
	// print_XYZ(1, &ray.dir);
	// printf("\n");
	// norm_vec(&ray.dir);
	return (ray);
}