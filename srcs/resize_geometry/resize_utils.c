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
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

void	changedimension(double *param, char *dimension)
{
	char	*new;

	printf("Enter the new %s:\n", dimension);
	new = get_next_line(0);
	if (!isdouble(new))
	{
		free(new);
		return ;
	}
	*param = ft_atof(new);
	if (*param < 0)
	{
		*param *= -1;
	}
	free(new);
}

void	changexyz(t_XYZ *xyz, char *type)
{
	char	*new;

	printf("Enter the new %s:\n", type);
	new = get_next_line(0);
	if (!is_xyz(new))
	{
		free(new);
		return ;
	}
	parse_xyz(new, xyz);
	free(new);
}

void	changecolour(t_colour *colour)
{
	char	*new;

	printf("Enter the new colour:\n");
	new = get_next_line(0);
	if (!is_colour(new))
	{
		free(new);
		return ;
	}
	parse_colour(new, colour);
	free(new);
}

void	copypos(t_XYZ *src, t_XYZ *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

void	copycolour(t_colour *src, t_colour *dst)
{
	dst->red = src->red;
	dst->green = src->green;
	dst->blue = src->blue;
	dst->transparency = src->transparency;
}
