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

int	searchcoord(t_rt *rt, t_geometry *geom, int posx, int posy)
{
	int	j;

	j = 0;
	while (j < rt->width * rt->height)
	{
		if (posx == (int)geom->screencoords[j].x
			&& posy == (int)geom->screencoords[j].y)
		{
			return (1);
		}
		++j;
	}
	return (0);
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
		i = 0;
		while (i < local_rt->scene->geomsize)
		{
			if (searchcoord(local_rt, objects[i],
					mousex, mousey))
				break ;
			++i;
		}
		if (i < local_rt->scene->geomsize)
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
		free(local_rt->scene->geometry.array[index]->screencoords);
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
	if (height < width)
		local_rt->aspectratio = (double)width / (double)height;
	else
		local_rt->aspectratio = (double)height / (double)width;
}

void	resize_render(void *param)
{
	t_rt		*local_rt;
	t_geometry	**objects;
	int			i;

	local_rt = (t_rt *)param;
	i = 0;
	if (local_rt->lastresize > 0 && (mlx_get_time() - local_rt->lastresize) > 0.1)
	{
		objects = local_rt->scene->geometry.array;
		while (i < local_rt->scene->geomsize)
		{
			free(objects[i]->screencoords);
			objects[i]->screencoords = ft_calloc((local_rt->height
				* local_rt->width) + 1, sizeof(t_XYZ));
			++i;
		}
		draw_objects(local_rt);
		local_rt->lastresize = 0;
	}
}

void	rotate_camera(void *param)
{
	t_rt	*local_rt;

	local_rt = (t_rt *)param;
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
	default_matrix_rotate(local_rt, local_rt->xrotation, local_rt->yrotation);
	draw_objects(local_rt);
}
