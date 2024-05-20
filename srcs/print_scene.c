/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:02:18 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/17 20:06:51 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

static void	print_colour(int fd, t_colour *colour)
{
	dprintf(fd, "%i,%i,%i", colour->red, colour->green, colour->blue);
}

static void	print_XYZ(int fd, t_XYZ *pos)
{
	dprintf(fd, "%f,%f,%f", pos->x, pos->y, pos->z);
}

static void	print_lighting(int fd, t_lighting **lights)
{
	t_lighting	*light;

	while (*lights)
	{
		light = *lights;
		dprintf(fd, "L ");
		print_XYZ(fd, &light->direction);
		dprintf(fd, " %f ", light->brightness);
		print_colour(fd, &light->colour);
		dprintf(fd, "\n");
		++lights;
	}
}

static void	print_sphere(int fd, t_sphere *sphere)
{
	dprintf(fd, "sp ");
	print_XYZ(fd, &sphere->centre);
	dprintf(fd, " %f %f ", sphere->diameter, sphere->radius);
	print_colour(fd, &sphere->colour);
	dprintf(fd, "\n");
}

static void	print_plane(int fd, t_plane *plane)
{
	dprintf(fd, "pl ");
	print_XYZ(fd, &plane->point);
	dprintf(fd, " ");
	print_XYZ(fd, &plane->normal);
	dprintf(fd, " ");
	print_colour(fd, &plane->colour);
	dprintf(fd, "\n");
}

static void	print_cylinder(int fd, t_cylinder *cylinder)
{
	dprintf(fd, "cy ");
	print_XYZ(fd, &cylinder->centre);
	dprintf(fd, " ");
	print_XYZ(fd, &cylinder->axis);
	dprintf(fd, " %f %f ", cylinder->diameter, cylinder->height);
	print_colour(fd, &cylinder->colour);
	dprintf(fd, "\n");
}

void	print_geometry(int fd, t_geometry **arr)
{
	t_geometry	*geom;

	while (*arr)
	{
		geom = *arr;
		if (ft_strncmp(geom->elemtype, "sphere", 7) == 0)
		{
			print_sphere(fd, geom->elem.sphere);
		}
		else if (ft_strncmp(geom->elemtype, "plane", 6) == 0)
		{
			print_plane(fd, geom->elem.plane);
		}
		else if (ft_strncmp(geom->elemtype, "cylinder", 9) == 0)
		{
			print_cylinder(fd, geom->elem.cylinder);
		}
		++arr;
	}
}

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
		print_XYZ(fd, &scene->cam.pos);
		dprintf(fd, " ");
		print_XYZ(fd, &scene->cam.viewdirection);
		dprintf(fd, " %i\n", scene->cam.fov);
	}
	if (scene->lighting.array)
		print_lighting(fd, scene->lighting.array);
	else
		dprintf(fd, "There is no lighting in this scene\n");
	if (scene->geometry.array)
		print_geometry(fd, scene->geometry.array);
}
