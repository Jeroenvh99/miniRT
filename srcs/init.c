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

void	write_scene(t_scene *scene)
{
	int	fd;

	fd = open(scene->filename, O_RDONLY | O_WRONLY | O_TRUNC);
	print_scene(fd, scene);
	close(fd);
}

void	draw_objects(t_rt *rt)
{
	t_drawfunc const	drawfuncs[3] = {draw_sphere, NULL, NULL};
	t_geometry			**objects;
	int					i;

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
	objects = rt->scene->geometry.array;
	i = 0;
	while (i < rt->scene->geomsize)
	{
		drawfuncs[objects[i]->elemtype - 1](rt, objects[i]);
		++i;
	}
}

void	init_rt(t_rt *rt)
{
	int			i;
	t_geometry	**objects;

	i = 0;
	rt->width = 1280;
	rt->height = 720;
	rt->aspectratio = (double)rt->width / (double)rt->height;
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", true);
	if (!rt->mlx)
	{
		exit(1);
	}
	rt->image = NULL;
	objects = rt->scene->geometry.array;
	while (i < rt->scene->geomsize)
	{
		objects[i]->screencoords = ft_calloc((rt->height * rt->width) + 1,
				sizeof(t_XYZ));
		++i;
	}
	i = 0;
	while (i < HISTORYSIZE)
	{
		rt->history[i].geom = NULL;
		++i;
	}
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
