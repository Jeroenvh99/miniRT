/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:13:12 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/08/03 17:01:22 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>

int	comment(char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	return (*str == '#');
}

char	*skipspace(char *in)
{
	if (!in)
		return (NULL);
	while (*in && ft_isspace(*in))
		++in;
	return (in);
}

void	tabtospace(char *str)
{
	while (*str)
	{
		if (*str == '\t')
			*str = ' ';
		++str;
	}
}

void	parse_colour(char *in, t_colour *colour)
{
	colour->red = ft_atoi(in);
	in = ft_strchr(in, ',') + 1;
	colour->green = ft_atoi(in);
	in = ft_strchr(in, ',') + 1;
	colour->blue = ft_atoi(in);
	colour->transparency = 255;
}

void	parse_xyz(char *in, t_XYZ *pos)
{
	pos->x = ft_atof(in);
	in = ft_strchr(in, ',') + 1;
	pos->y = ft_atof(in);
	in = ft_strchr(in, ',') + 1;
	pos->z = ft_atof(in);
}
