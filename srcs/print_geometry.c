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

static void	print_sphere(int fd, t_sphere *sphere)
{
	dprintf(fd, "sp ");
	print_xyz(fd, &sphere->centre);
	dprintf(fd, " %f ", sphere->radius * 2);
	print_colour(fd, &sphere->colour);
	dprintf(fd, "\n");
}

static void	print_plane(int fd, t_plane *plane)
{
	dprintf(fd, "pl ");
	print_xyz(fd, &plane->point);
	dprintf(fd, " ");
	print_xyz(fd, &plane->normal);
	dprintf(fd, " ");
	print_colour(fd, &plane->colour);
	dprintf(fd, "\n");
}

static void	print_cylinder(int fd, t_cylinder *cylinder)
{
	dprintf(fd, "cy ");
	print_xyz(fd, &cylinder->centre);
	dprintf(fd, " ");
	print_xyz(fd, &cylinder->axis);
	dprintf(fd, " %f %f ", cylinder->radius * 2, cylinder->height);
	print_colour(fd, &cylinder->colour);
	dprintf(fd, "\n");
}

void	print_geometry(int fd, t_geometry **arr)
{
	t_geometry	*geom;

	while (*arr)
	{
		geom = *arr;
		if (geom->elemtype == 1)
		{
			print_sphere(fd, (t_sphere *)geom->elem);
		}
		else if (geom->elemtype == 2)
		{
			print_plane(fd, (t_plane *)geom->elem);
		}
		else if (geom->elemtype == 3)
		{
			print_cylinder(fd, (t_cylinder *)geom->elem);
		}
		++arr;
	}
}
