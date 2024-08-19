/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize_geometry.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 09:54:26 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/02/12 13:12:52 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

static void	resize_plane(t_plane *plane)
{
	char	*selection;

	printf("P to change the point\nN to change the normal direction\n"
		"C to change the colour\n");
	selection = get_next_line(0);
	if (*selection == 'P' && ft_strlen(selection) == 2)
	{
		changexyz(&plane->point, "point");
	}
	else if (*selection == 'N' && ft_strlen(selection) == 2)
	{
		changexyz(&plane->normal, "normal");
	}
	else if (*selection == 'C' && ft_strlen(selection) == 2)
	{
		changecolour(&plane->colour);
	}
	free(selection);
}

static void	resize_sphere(t_sphere *sphere)
{
	char	*selection;

	printf("X to change the centre\nR to change the radius\n"
		"C to change the colour\n");
	selection = get_next_line(0);
	if (*selection == 'X' && ft_strlen(selection) == 2)
	{
		changexyz(&sphere->centre, "centre");
	}
	else if (*selection == 'R' && ft_strlen(selection) == 2)
	{
		changedimension(&sphere->radius, "radius");
	}
	else if (*selection == 'C' && ft_strlen(selection) == 2)
	{
		changecolour(&sphere->colour);
	}
	free(selection);
}

static void	resize_cylinder(t_cylinder *cylinder)
{
	char	*selection;

	printf("X to change the centre\nA to change the axis\n"
		"D to change the diameter\nR to change the radius\n"
		"H to change the height\nC to change the colour\n");
	selection = get_next_line(0);
	if (*selection == 'X' && ft_strlen(selection) == 2)
	{
		changexyz(&cylinder->centre, "centre");
	}
	else if (*selection == 'A' && ft_strlen(selection) == 2)
	{
		changexyz(&cylinder->axis, "axis");
	}
	else if (*selection == 'R' && ft_strlen(selection) == 2)
	{
		changedimension(&cylinder->radius, "radius");
	}
	else if (*selection == 'H' && ft_strlen(selection) == 2)
	{
		changedimension(&cylinder->height, "height");
	}
	else if (*selection == 'C' && ft_strlen(selection) == 2)
	{
		changecolour(&cylinder->colour);
	}
	free(selection);
}

void	resize_elements(t_rt *rt, int i)
{
	t_geometry	**objects;
	int			j;

	j = 0;
	while (rt->history[j].geom && j < HISTORYSIZE)
	{
		++j;
	}
	if (j == HISTORYSIZE)
	{
		free(rt->history[0].geom->elem);
		free(rt->history[0].geom);
		moveback(rt->history);
		--j;
	}
	objects = rt->scene->geometry.array;
	rt->history[j].index = i;
	rt->history[j].geom = objects[i];
	printf("Element type: %i\n1 = sphere, 2 = plane, 3 = cylinder\n",
		objects[i]->elemtype);
	if (objects[i]->elemtype == 1)
	{
		rt->scene->geometry.array[i] = copygeom(objects[i]);
		resize_sphere((t_sphere *)objects[i]->elem);
	}
	else if (objects[i]->elemtype == 2)
	{
		rt->scene->geometry.array[i] = copygeom(objects[i]);
		resize_plane((t_plane *)objects[i]->elem);
	}
	else if (objects[i]->elemtype == 3)
	{
		rt->scene->geometry.array[i] = copygeom(objects[i]);
		resize_cylinder((t_cylinder *)objects[i]->elem);
	}
	rt->scene->isresized = 1;
}
