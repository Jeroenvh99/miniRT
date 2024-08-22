/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:02:18 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/08/08 16:43:24 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

void	print_scene(int fd, t_scene *scene)
{
	if (scene->amb.intensity <= 100)
	{
		dprintf(fd, "A %f ", scene->amb.intensity);
		print_colour(fd, &scene->amb.colour);
		dprintf(fd, "\n");
	}
	if (scene->cam.fov <= 180)
	{
		dprintf(fd, "C ");
		print_xyz(fd, &scene->cam.pos);
		dprintf(fd, " ");
		print_xyz(fd, &scene->cam.viewdirection);
		dprintf(fd, " %i\n", scene->cam.fov);
	}
	print_lighting(fd, scene->lighting.array);
	if (scene->geometry.array)
		print_geometry(fd, scene->geometry.array);
}
