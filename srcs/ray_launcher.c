/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:48:19 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/04 16:23:49 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <stdio.h>

void	default_matrix(t_rt *rt)
{
	rt->camtransform[0][0] = 1;
	rt->camtransform[0][1] = 0;
	rt->camtransform[0][2] = 0;
	rt->camtransform[1][0] = 0;
	rt->camtransform[1][1] = 1;
	rt->camtransform[1][2] = 0;
	rt->camtransform[2][0] = 0;
	rt->camtransform[2][1] = 0;
	rt->camtransform[2][2] = 1;
}

void	default_matrix_rotate(t_rt *rt, double xrotation, double yrotation)
{
	rt->camtransform[0][0] = cos(xrotation) + cos(yrotation);
	rt->camtransform[0][1] = sin(yrotation);
	rt->camtransform[0][2] = -sin(xrotation);
	rt->camtransform[1][0] = -sin(yrotation);
	rt->camtransform[1][1] = cos(yrotation);
	rt->camtransform[1][2] = 0;
	rt->camtransform[2][0] = sin(xrotation);
	rt->camtransform[2][1] = 0;
	rt->camtransform[2][2] = cos(xrotation);
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
	return (res);
}

t_ray	ray_launcher(t_rt *rt, t_ray ray, double x, double y)
{
	double scale;

	scale = tan((double)rt->scene->cam.fov * 0.5 * M_PI / 180);
	ray.origin = rt->scene->cam.pos;
	ray.dir.x = (2.0 * (x + 0.5) / (double)rt->width - 1.0) * scale
		* rt->aspectratio;
	ray.dir.z = (1.0 - 2.0 * (y + 0.5) / (double)rt->height) * scale;
	ray.dir.y = 1.0;
	norm_vec(&ray.dir);
	return (ray);
}