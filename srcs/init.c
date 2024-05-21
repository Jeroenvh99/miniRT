/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:40:24 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/21 12:36:34 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	buildcamtransform(t_rt *rt)
{
	t_XYZ	*forward;

	t_XYZ right, up, tmp;
	tmp = vector(0, 1, 0);
	forward = &rt->scene->cam.viewdirection;
	*forward = norm_vec(*forward);
	right = cross_vec(tmp, *forward);
	up = cross_vec(*forward, right);
	rt->camtransform[0][0] = right.x;
	rt->camtransform[0][1] = right.y;
	rt->camtransform[0][2] = right.z;
	rt->camtransform[1][0] = up.x;
	rt->camtransform[1][1] = up.y;
	rt->camtransform[1][2] = up.z;
	rt->camtransform[2][0] = forward->x;
	rt->camtransform[2][1] = forward->y;
	rt->camtransform[2][2] = forward->z;
}

void	write_scene(t_scene *scene)
{
	int	fd;

	fd = open(scene->filename, O_RDONLY | O_WRONLY | O_TRUNC);
	print_scene(fd, scene);
	close(fd);
}

void	draw_objects(t_rt *rt)
{
	t_geometry **objects = rt->scene->geometry.array;
	int i = 0;
	while (i < rt->scene->geomsize)
	{
		if (objects[i]->elemtype == 1)
		{
			draw_sphere(rt, *(objects[i]->elem.sphere));
		}
		// else if (objects[i]->elemtype == 2)
		// {
		// 	draw_cylinder(rt, *(objects[i]->elem.cylinder));
		// }
		// else if (objects[i]->elemtype == 3)
		// {
		// 	draw_plane(rt, *(objects[i]->elem.plane));
		// }
		++i;
	}
}

void	init_rt(t_rt *rt)
{
	rt->width = 1280;
	rt->height = 720;
	if (rt->height < rt->width)
		rt->aspectratio = rt->width / rt->height;
	else
		rt->aspectratio = rt->height / rt->width;
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", false);
	if (!rt->mlx)
	{
		exit(1);
	}
	rt->image = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->image || mlx_image_to_window(rt->mlx, rt->image, 0, 0) < 0)
	{
		mlx_terminate(rt->mlx);
		exit(1);
	}
}

void	exit_rt(t_rt *rt)
{
	char	*res;

	mlx_terminate(rt->mlx);
	if (rt->scene->isresized)
	{
		write(1, "Do you want to save the updated scene[Y/N]:", 43);
		res = get_next_line(0);
		if (*res == 'y' || *res == 'Y')
		{
			write_scene(rt->scene);
		}
		free(res);
	}
	free_scene(rt->scene, 1);
	exit(1);
}
