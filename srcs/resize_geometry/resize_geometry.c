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
	if (*selection == 'P' && ft_strlen(selection) == 1)
	{
		changexyz(&plane->point, "point");
	}
	else if (*selection == 'N' && ft_strlen(selection) == 1)
	{
		changexyz(&plane->normal, "normal");
	}
	else if (*selection == 'C' && ft_strlen(selection) == 1)
	{
		changecolour(&plane->colour);
	}
	free(selection);
}

static void	resize_sphere(t_sphere *sphere)
{
	char	*selection;

	printf("X to change the centre\nD to change the diameter\n"
			"R to change the radius\nC to change the colour\n");
	selection = get_next_line(0);
	if (*selection == 'X' && ft_strlen(selection) == 1)
	{
		changexyz(&sphere->centre, "centre");
	}
	else if (*selection == 'D' && ft_strlen(selection) == 1)
	{
		changedimension(&sphere->diameter, "diameter");
	}
	else if (*selection == 'R' && ft_strlen(selection) == 1)
	{
		changedimension(&sphere->radius, "radius");
	}
	else if (*selection == 'C' && ft_strlen(selection) == 1)
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
	if (*selection == 'X' && ft_strlen(selection) == 1)
	{
		changexyz(&cylinder->centre, "centre");
	}
	else if (*selection == 'A' && ft_strlen(selection) == 1)
	{
		changexyz(&cylinder->axis, "axis");
	}
	else if (*selection == 'D' && ft_strlen(selection) == 1)
	{
		changedimension(&cylinder->diameter, "diameter");
	}
	else if (*selection == 'R' && ft_strlen(selection) == 1)
	{
		changedimension(&cylinder->radius, "radius");
	}
	else if (*selection == 'H' && ft_strlen(selection) == 1)
	{
		changedimension(&cylinder->height, "height");
	}
	else if (*selection == 'C' && ft_strlen(selection) == 1)
	{
		changecolour(&cylinder->colour);
	}
	free(selection);
}

void	resize_elements(t_rt *rt)
{
	int		i;
	char	*num;

	while (1)
	{
		printf("Enter the ID of the element you'd like to change:\nOr exit to exit editing mode\n");
		i = -1;
		while (i < 0 || i >= rt->scene->geomsize)
		{
			num = get_next_line(0);
			if (ft_strncmp(num, "exit", 4) == 0)
			{
				free(num);
				return;
			}
			i = ft_atoi(num);
			free(num);
		}
		printf("Element type: %i\n 1 = sphere, 2 = plane, 3 = cylinder\n", rt->scene->geometry.array[i]->elemtype);
		if (rt->scene->geometry.array[i]->elemtype == 2)
		{
			resize_plane(rt->scene->geometry.array[i]->elem.plane);
		}
		else if (rt->scene->geometry.array[i]->elemtype == 1)
		{
			resize_sphere(rt->scene->geometry.array[i]->elem.sphere);
		}
		else if (rt->scene->geometry.array[i]->elemtype == 3)
		{
			resize_cylinder(rt->scene->geometry.array[i]->elem.cylinder);
		}
		rt->scene->isresized = 1;
		print_scene(1, rt->scene); // for testing purposes
	}
}
