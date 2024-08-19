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

void	print_colour(int fd, t_colour *colour)
{
	dprintf(fd, "%f,%f,%f", colour->red, colour->green, colour->blue);
}

void	print_xyz(int fd, t_XYZ *pos)
{
	dprintf(fd, "%f,%f,%f", pos->x, pos->y, pos->z);
}

void	print_lighting(int fd, t_lighting **lights)
{
	t_lighting	*light;

	while (*lights)
	{
		light = *lights;
		dprintf(fd, "L ");
		print_xyz(fd, &light->direction);
		dprintf(fd, " %f ", light->brightness);
		print_colour(fd, &light->colour);
		dprintf(fd, "\n");
		++lights;
	}
}
