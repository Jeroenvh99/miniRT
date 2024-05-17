/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_check_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 13:49:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/01/16 15:38:01 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <unistd.h>

int	checkcamera(char **parts)
{
	if (splitsize(parts) != 4)
	{
		write(2, "Error\nToo little information for camera\n", 40);
		return (0);
	}
	if (!is_xyz(parts[1]))
	{
		write(2, "Error\nIncorrect position for camera\n", 36);
		return (0);
	}
	if (!is_xyz(parts[2]))
	{
		write(2, "Error\nIncorrect viewdirection for camera\n", 41);
		return (0);
	}
	if (!isint(parts[3]))
	{
		write(2, "Error\nIncorrect field of view for camera\n", 41);
		return (0);
	}
	return (1);
}

int	checklight(char **parts)
{
	if (splitsize(parts) != 4)
	{
		write(2, "Error\nToo little information for light\n", 39);
		return (0);
	}
	if (!is_xyz(parts[1]))
	{
		write(2, "Error\nIncorrect position for spot\n", 34);
		return (0);
	}
	if (!isdouble(parts[2]))
	{
		write(2, "Error\nIncorrect brightness for spot\n", 36);
		return (0);
	}
	if (!is_colour(parts[3]))
	{
		write(2, "Error\nIncorrect colour for spot\n", 32);
		return (0);
	}
	return (1);
}

int	checksphere(char **parts)
{
	if (splitsize(parts) != 4)
	{
		write(2, "Error\nToo little information for sphere\n", 40);
		return (0);
	}
	if (!is_xyz(parts[1]))
	{
		write(2, "Error\nIncorrect centre for sphere\n", 34);
		return (0);
	}
	if (!isdouble(parts[2]))
	{
		write(2, "Error\nIncorrect diameter for sphere\n", 36);
		return (0);
	}
	if (!is_colour(parts[3]))
	{
		write(2, "Error\nIncorrect colour for sphere\n", 34);
		return (0);
	}
	return (1);
}

int	checkplane(char **parts)
{
	if (splitsize(parts) != 4)
	{
		write(2, "Error\nToo little information for plane\n", 39);
		return (0);
	}
	if (!is_xyz(parts[1]))
	{
		write(2, "Error\nIncorrect point for plane\n", 32);
		return (0);
	}
	if (!is_xyz(parts[2]))
	{
		write(2, "Error\nIncorrect normal for plane\n", 33);
		return (0);
	}
	if (!is_colour(parts[3]))
	{
		write(2, "Error\nIncorrect colour for plane\n", 33);
		return (0);
	}
	return (1);
}

int	checkcylinder(char **parts)
{
	if (splitsize(parts) != 6)
	{
		write(2, "Error\nToo little information for cylinder\n", 42);
		return (0);
	}
	if (!is_xyz(parts[1]))
	{
		write(2, "Error\nIncorrect centre for cylinder\n", 36);
		return (0);
	}
	if (!is_xyz(parts[2]))
	{
		write(2, "Error\nIncorrect axis for cylinder\n", 34);
		return (0);
	}
	if (!parse_cylinder_2(parts))
	{
		return (0);
	}
	return (1);
}
