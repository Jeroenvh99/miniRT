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
#include <stdio.h>

void	escape_hook(void *param)
{
	mlx_t	*mlx;

	mlx = ((t_rt *)param)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		exit_rt((t_rt *)param);
}

int	searchcoord(t_rt *rt, t_geometry *geom, int posx, int posy)
{
	int j = 0;
	while (j < rt->width * rt->height)
		{
			if (posx == (int)geom->screencoords[j].x && posy == (int)geom->screencoords[j].y)
			{
				return 1;
			}
			++j;
		}
		return 0;
}

void	set_resize(void *param)
{
	t_rt	*local_rt;

	local_rt = (t_rt *)param;
	if (mlx_is_mouse_down(local_rt->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		t_geometry	**objects;
	int			i;
	int	mousex;
	int mousey;

	mlx_get_mouse_pos(local_rt->mlx, &mousex, &mousey);
	objects = local_rt->scene->geometry.array;
	i = 0;
	while (i < local_rt->scene->geomsize)
	{
		t_geometry *geom = local_rt->scene->geometry.array[i];
		if (searchcoord(local_rt, geom, mousex, mousey))
			break;
		++i;
	}
		printf("%i", i);
		resize_elements(local_rt, i);
		draw_objects(local_rt);
	}
}
