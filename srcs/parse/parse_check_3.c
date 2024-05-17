/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_check_3.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 15:35:35 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/01/17 11:16:24 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <unistd.h>

int	parse_cylinder_2(char **parts)
{
	if (!isdouble(parts[3]))
	{
		write(2, "Error\nIncorrect diameter for cylinder\n", 38);
		return (0);
	}
	if (!isdouble(parts[4]))
	{
		write(2, "Error\nIncorrect height for cylinder\n", 36);
		return (0);
	}
	if (!is_colour(parts[5]))
	{
		write(2, "Error\nIncorrect colour for cylinder\n", 36);
		return (0);
	}
	return (1);
}
