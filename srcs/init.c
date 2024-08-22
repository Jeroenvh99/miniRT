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
#include <stdlib.h>

void	reset_pixeldata(t_rt *rt)
{
	int	x;
	int	y;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			rt->pixeldata[y * rt->width + x].dist = 1.7976931348623157E+308;
			rt->pixeldata[y * rt->width + x].colour = 0x000000FF;
			x++;
		}
		y++;
	}
}

void	render_objects(t_rt *rt)
{
	t_drawfunc const	drawfuncs[3] = {draw_sphere, draw_plane, draw_cylinder};
	t_geometry			**objects;
	int					i;

	objects = rt->scene->geometry.array;
	i = 0;
	while (i < rt->scene->geomsize)
	{
		drawfuncs[objects[i]->elemtype - 1](rt, objects[i], i);
		++i;
	}
}

void	reset_image(t_rt *rt)
{
	if (rt->image)
		mlx_delete_image(rt->mlx, rt->image);
	rt->image = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->image || mlx_image_to_window(rt->mlx, rt->image, 0, 0) < 0)
	{
		mlx_terminate(rt->mlx);
		exit(1);
	}
}

void	draw_objects(t_rt *rt)
{
	int	x;
	int	y;

	reset_image(rt);
	reset_pixeldata(rt);
	render_objects(rt);
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			if (rt->pixeldata[y * rt->width + x].dist
				!= 1.7976931348623157E+308)
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
	int	i;

	rt->width = 1280;
	rt->height = 720;
	rt->totalpixels = 1280 * 720;
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", true);
	rt->pixeldata = malloc(rt->totalpixels * sizeof(t_hit));
	if (!rt->mlx || !rt->pixeldata)
		exit(1);
	rt->lastresize = 0;
	rt->aspectratio = (double)rt->width / (double)rt->height;
	rt->xrotation = 0;
	rt->yrotation = 0;
	rt->zrotation = 0;
	rt->image = NULL;
	i = 0;
	while (i < HISTORYSIZE)
	{
		rt->history[i].geom = NULL;
		++i;
	}
	default_matrix_rotate(rt, 0, 0, 0);
}
