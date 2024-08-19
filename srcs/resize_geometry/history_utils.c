/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 09:55:42 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/02/05 10:07:57 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

void	*copysphere(void *sourceelem)
{
	t_sphere	*source;
	t_sphere	*res;

	source = (t_sphere *)sourceelem;
	res = ft_calloc(1, sizeof(t_sphere));
	copypos(&source->centre, &res->centre);
	res->radius = source->radius;
	copycolour(&source->colour, &res->colour);
	return (res);
}

void	*copyplane(void *sourceelem)
{
	t_plane	*source;
	t_plane	*res;

	source = (t_plane *)sourceelem;
	res = ft_calloc(1, sizeof(t_plane));
	copypos(&source->point, &res->point);
	copypos(&source->normal, &res->normal);
	copycolour(&source->colour, &res->colour);
	return (res);
}

void	*copycylinder(void *sourceelem)
{
	t_cylinder	*source;
	t_cylinder	*res;

	source = (t_cylinder *)sourceelem;
	res = ft_calloc(1, sizeof(t_cylinder));
	copypos(&source->centre, &res->centre);
	copypos(&source->axis, &res->axis);
	res->radius = source->radius;
	res->height = source->height;
	copycolour(&source->colour, &res->colour);
	return (res);
}

t_geometry	*copygeom(t_geometry *source)
{
	t_geometry			*copy;
	t_copyfunc const	copyfuncs[3] = {copysphere, copyplane, copycylinder};

	copy = ft_calloc(1, sizeof(t_geometry));
	copy->elemtype = source->elemtype;
	copy->elem = copyfuncs[source->elemtype - 1](source->elem);
	return (copy);
}

void	moveback(t_history *history)
{
	int	i;

	i = 1;
	while (i < HISTORYSIZE)
	{
		history[i - 1].index = history[i].index;
		history[i - 1].geom = history[i].geom;
		++i;
	}
	history[i - 1].geom = NULL;
}
