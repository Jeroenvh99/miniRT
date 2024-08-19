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
	t_rt	*rt;

	rt = (t_rt *)param;
	if (mlx_is_key_down(rt->mlx, MLX_KEY_ESCAPE))
		exit_rt(rt);
}

void	rotate_camera(void *param)
{
	t_rt	*rt;
	double	prevxrot;
	double	prevyrot;
	double	prevzrot;

	rt = (t_rt *)param;
	prevxrot = rt->xrotation;
	prevyrot = rt->yrotation;
	prevzrot = rt->zrotation;
	if (mlx_is_key_down(rt->mlx, MLX_KEY_LEFT))
	{
		rt->xrotation += 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(rt->mlx, MLX_KEY_RIGHT))
	{
		rt->xrotation -= 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(rt->mlx, MLX_KEY_UP))
	{
		rt->yrotation += 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(rt->mlx, MLX_KEY_DOWN))
	{
		rt->yrotation -= 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(rt->mlx, MLX_KEY_W))
	{
		rt->zrotation += 5 * (M_PI / 180.0);
	}
	else if (mlx_is_key_down(rt->mlx, MLX_KEY_S))
	{
		rt->zrotation -= 5 * (M_PI / 180.0);
	}
	if (rt->xrotation != prevxrot || rt->yrotation != prevyrot || prevzrot != rt->zrotation)
	{
		default_matrix_rotate(rt, rt->xrotation, rt->yrotation, rt->zrotation);
		draw_objects(rt);
	}
}
