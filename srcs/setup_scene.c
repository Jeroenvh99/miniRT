/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:22:01 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/17 20:02:48 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>
#include <unistd.h>

int	checkfilename(char *file)
{
	file = ft_strrchr(file, '.');
	if (file && ft_strncmp(file, ".rt", 4) == 0)
		return (1);
	write(2, "Error\nIncorrect inputfile, use the .rt extension\n", 49);
	return (0);
}

t_scene	*initscene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit(1);
	scene->isresized = 0;
	scene->amb.intensity = 101;
	scene->cam.fov = 181;
	scene->lighting.list = NULL;
	scene->geometry.list = NULL;
	return (scene);
}

void	free_geom(void *geometry)
{
	t_geometry	*geom;

	geom = (t_geometry *)geometry;
	free(geom->elem);
	free(geom);
}

void	free_arr(void **arr, void (*del)(void *))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		(*del)(arr[i]);
		arr[i] = NULL;
		++i;
	}
	free(arr);
	arr = NULL;
}

void	free_scene(t_scene *scene, int isarr)
{
	if (isarr)
	{
		free_arr((void **)scene->lighting.array, free);
		free_arr((void **)scene->geometry.array, free_geom);
	}
	else
	{
		ft_lstclear(&scene->lighting.list, free);
		ft_lstclear(&scene->geometry.list, free_geom);
	}
	free(scene);
}
