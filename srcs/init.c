/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:40:24 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/08/19 15:46:12 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	write_scene(t_scene *scene)
{
	int	fd;

	fd = open(scene->filename, O_RDONLY | O_WRONLY | O_TRUNC);
	print_scene(fd, scene);
	close(fd);
}

void	draw_objects(t_rt *rt)
{
	t_drawfunc const	drawfuncs[3] = {draw_sphere, draw_plane, draw_cylinder};
	t_geometry			**objects;
	int					x;
	int					y;

	if (rt->image)
	{
		mlx_delete_image(rt->mlx, rt->image);
	}
	rt->image = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->image || mlx_image_to_window(rt->mlx, rt->image, 0, 0) < 0)
	{
		mlx_terminate(rt->mlx);
		exit(1);
	}
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			rt->pixeldata[y * rt->width + x].dist = DBL_MAX;
			rt->pixeldata[y * rt->width + x].colour = 0x000000FF;
			x++;
		}
		y++;
	}
	objects = rt->scene->geometry.array;
	y = 0;
	while (y < rt->scene->geomsize)
	{
		drawfuncs[objects[y]->elemtype - 1](rt, objects[y], y);
		++y;
	}
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			if (rt->pixeldata[y * rt->width + x].dist != DBL_MAX)
			{
				mlx_put_pixel(rt->image, x, y,
					rt->pixeldata[y * rt->width + x].colour);
			}
			x++;
		}
		y++;
	}
}

void	init_rt(t_rt *rt)
{
	int			i;
	t_geometry	**objects;

	i = 0;
	rt->width = 1280;
	rt->height = 720;
	rt->totalpixels = 1280 * 720;
	rt->lastresize = 0;
	rt->aspectratio = (double)rt->width / (double)rt->height;
	rt->xrotation = 0;
	rt->yrotation = 0;
	rt->zrotation = 0;
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", true);
	if (!rt->mlx)
		exit(1);
	rt->pixeldata = malloc(rt->totalpixels * sizeof(t_hit));
	if (!rt->pixeldata)
		exit(1);
	rt->image = NULL;
	objects = rt->scene->geometry.array;
	i = 0;
	while (i < HISTORYSIZE)
	{
		rt->history[i].geom = NULL;
		++i;
	}
	default_matrix_rotate(rt, 0, 0, 0);
}

void	exit_rt(t_rt *rt)
{
	char	*res;
	int		i;

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
	free(rt->pixeldata);
	i = 0;
	while (i < HISTORYSIZE)
	{
		if (rt->history[i].geom)
		{
			free(rt->history[i].geom);
		}
		++i;
	}
	exit(0);
}
