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
			write_scene(rt->scene);
		free(res);
	}
	free_scene(rt->scene, 1);
	free(rt->pixeldata);
	i = 0;
	while (i < HISTORYSIZE)
	{
		if (rt->history[i].geom)
		{
			free_geom(rt->history[i].geom);
		}
		++i;
	}
	exit(0);
}
