/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 09:57:37 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/02/09 14:31:27 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	searchcoord(t_rt *rt, int posx, int posy)
{
	int	x;
	int	y;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			if (rt->pixeldata[y * rt->width + x].dist != DBL_MAX)
			{
				if (x == posx && y == posy)
					return (rt->pixeldata[y * rt->width + x].elemid);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

void	set_resize(void *param)
{
	t_rt		*rt;
	t_geometry	**objects;
	int			i;
	int			mousex;
	int			mousey;

	rt = (t_rt *)param;
	if (mlx_is_mouse_down(rt->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(rt->mlx, &mousex, &mousey);
		objects = rt->scene->geometry.array;
		i = searchcoord(rt, mousex, mousey);
		if (i > -1 && i < rt->scene->geomsize)
		{
			resize_elements(rt, i);
			draw_objects(rt);
		}
	}
}

void	reset_resize(mlx_key_data_t keydata, void *param)
{
	t_rt	*rt;
	int		index;
	int		j;

	rt = (t_rt *)param;
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS
		&& keydata.modifier == MLX_CONTROL)
	{
		j = 0;
		while (rt->history[j + 1].geom && j < HISTORYSIZE - 2)
		{
			++j;
		}
		if (!rt->history[j].geom)
		{
			return ;
		}
		index = rt->history[j].index;
		free(rt->scene->geometry.array[index]->elem);
		free(rt->scene->geometry.array[index]);
		rt->scene->geometry.array[index] = rt->history[j].geom;
		rt->history[j].geom = NULL;
		draw_objects(rt);
	}
}

void	resize_rt(int32_t width, int32_t height, void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	rt->lastresize = mlx_get_time();
	rt->width = width;
	rt->height = height;
	rt->totalpixels = width * height;
	if (height < width)
		rt->aspectratio = (double)width / (double)height;
	else
		rt->aspectratio = (double)height / (double)width;
}

void	resize_render(void *param)
{
	t_rt	*rt;

	rt = (t_rt *)param;
	if (rt->lastresize > 0 && (mlx_get_time() - rt->lastresize) > 0.1)
	{
		free(rt->pixeldata);
		rt->pixeldata = malloc(rt->totalpixels * sizeof(t_hit));
		draw_objects(rt);
		rt->lastresize = 0;
	}
}
