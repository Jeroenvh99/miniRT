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

void	escape_hook(void *param)
{
	t_rt	*local_rt;

	local_rt = (t_rt *)param;
	if (mlx_is_key_down(local_rt->mlx, MLX_KEY_ESCAPE))
		exit_rt(local_rt);
}

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
	t_rt		*local_rt;
	t_geometry	**objects;
	int			i;
	int			mousex;
	int			mousey;

	local_rt = (t_rt *)param;
	if (mlx_is_mouse_down(local_rt->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(local_rt->mlx, &mousex, &mousey);
		objects = local_rt->scene->geometry.array;
		i = searchcoord(local_rt, mousex, mousey);
		if (i > -1 && i < local_rt->scene->geomsize)
		{
			resize_elements(local_rt, i);
			draw_objects(local_rt);
		}
	}
}

void	reset_resize(mlx_key_data_t keydata, void *param)
{
	t_rt	*local_rt;
	int		index;
	int		j;

	local_rt = (t_rt *)param;
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS
		&& keydata.modifier == MLX_CONTROL)
	{
		j = 0;
		while (local_rt->history[j + 1].geom && j < HISTORYSIZE - 2)
		{
			++j;
		}
		if (!local_rt->history[j].geom)
		{
			return ;
		}
		index = local_rt->history[j].index;
		free(local_rt->scene->geometry.array[index]->elem);
		free(local_rt->scene->geometry.array[index]);
		local_rt->scene->geometry.array[index] = local_rt->history[j].geom;
		local_rt->history[j].geom = NULL;
		draw_objects(local_rt);
	}
}

void	resize_rt(int32_t width, int32_t height, void *param)
{
	t_rt	*local_rt;

	local_rt = (t_rt *)param;
	local_rt->lastresize = mlx_get_time();
	local_rt->width = width;
	local_rt->height = height;
	local_rt->totalpixels = width * height;
	if (height < width)
		local_rt->aspectratio = (double)width / (double)height;
	else
		local_rt->aspectratio = (double)height / (double)width;
}

void	resize_render(void *param)
{
	t_rt	*local_rt;

	local_rt = (t_rt *)param;
	if (local_rt->lastresize > 0 && (mlx_get_time() - local_rt->lastresize) > 0.1)
	{
		free(local_rt->pixeldata);
		local_rt->pixeldata = malloc(local_rt->totalpixels * sizeof(t_hit));
		draw_objects(local_rt);
		local_rt->lastresize = 0;
	}
}

void	rotate_camera(void *param)
{
	t_rt	*local_rt;
	double	prevxrot;
	double	prevyrot;
	double	prevzrot;

	local_rt = (t_rt *)param;
	prevxrot = local_rt->xrotation;
	prevyrot = local_rt->yrotation;
	prevzrot = local_rt->zrotation;
	if (mlx_is_key_down(local_rt->mlx, MLX_KEY_LEFT))
	{
		local_rt->xrotation += 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(local_rt->mlx, MLX_KEY_RIGHT))
	{
		local_rt->xrotation -= 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(local_rt->mlx, MLX_KEY_UP))
	{
		local_rt->yrotation += 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(local_rt->mlx, MLX_KEY_DOWN))
	{
		local_rt->yrotation -= 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(local_rt->mlx, MLX_KEY_W))
	{
		local_rt->zrotation += 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(local_rt->mlx, MLX_KEY_S))
	{
		local_rt->zrotation -= 5 * (M_PI / 180.0);
	}
	if (local_rt->xrotation != prevxrot || local_rt->yrotation != prevyrot || prevzrot != local_rt->zrotation)
	{
		default_matrix_rotate(local_rt, local_rt->xrotation, local_rt->yrotation, local_rt->zrotation);
		draw_objects(local_rt);
	}
}
