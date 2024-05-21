/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_geometry.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 13:18:02 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/02/12 13:13:28 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parse.h"
#include <stdlib.h>

int	parsesphere(t_scene *scene, char *line)
{
	t_sphere	*sphere;
	char		**parts;
	t_geometry	*geom;

	parts = ft_split(line, ' ');
	geom = malloc(sizeof(t_geometry));
	sphere = malloc(sizeof(t_sphere));
	if (!geom || !sphere || !checksphere(parts))
	{
		free_split(parts);
		return (0);
	}
	parse_xyz(parts[1], &sphere->centre);
	sphere->diameter = ft_atof(parts[2]);
	sphere->radius = sphere->diameter * 0.5;
	parse_colour(parts[3], &sphere->colour);
	geom->elemtype = 1;
	geom->elem.sphere = sphere;
	ft_lstadd_back(&scene->geometry.list, ft_lstnew(geom));
	free_split(parts);
	return (1);
}

int	parseplane(t_scene *scene, char *line)
{
	t_plane		*plane;
	char		**parts;
	t_geometry	*geom;

	parts = ft_split(line, ' ');
	geom = malloc(sizeof(t_geometry));
	plane = malloc(sizeof(t_plane));
	if (!geom || !plane || !checkplane(parts))
	{
		free_split(parts);
		return (0);
	}
	parse_xyz(parts[1], &plane->point);
	parse_xyz(parts[2], &plane->normal);
	parse_colour(parts[3], &plane->colour);
	geom->elemtype = 2;
	geom->elem.plane = plane;
	ft_lstadd_back(&scene->geometry.list, ft_lstnew(geom));
	free_split(parts);
	return (1);
}

int	parsecylinder(t_scene *scene, char *line)
{
	t_cylinder	*cylinder;
	char		**parts;
	t_geometry	*geom;

	parts = ft_split(line, ' ');
	cylinder = malloc(sizeof(t_cylinder));
	geom = malloc(sizeof(t_geometry));
	if (!cylinder || !checkcylinder(parts))
	{
		free_split(parts);
		return (0);
	}
	parse_xyz(parts[1], &cylinder->centre);
	parse_xyz(parts[2], &cylinder->axis);
	cylinder->diameter = ft_atof(parts[3]);
	cylinder->radius = cylinder->diameter * 0.5;
	cylinder->height = ft_atof(parts[4]);
	parse_colour(parts[5], &cylinder->colour);
	geom->elemtype = 3;
	geom->elem.cylinder = cylinder;
	ft_lstadd_back(&scene->geometry.list, ft_lstnew(geom));
	free_split(parts);
	return (1);
}
