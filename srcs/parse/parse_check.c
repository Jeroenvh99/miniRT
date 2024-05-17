/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 13:47:31 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/01/16 14:22:52 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include <unistd.h>

int	isint(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && !ft_isspace(*str))
			return (0);
		++str;
	}
	return (1);
}

int	isdouble(char *str)
{
	int	dot;

	dot = 0;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.' && *str != '+' && *str != '-'
			&& !ft_isspace(*str))
			return (0);
		if (!dot && *str == '.')
			dot = 1;
		else if (dot && !ft_isdigit(*str) && !ft_isspace(*str))
			return (0);
		++str;
	}
	return (1);
}

int	is_colour(char *str)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (splitsize(parts) != 3)
	{
		free_split(parts);
		return (0);
	}
	if (!isint(parts[0]) || !isint(parts[1]) || !isint(parts[2]))
	{
		free_split(parts);
		return (0);
	}
	free_split(parts);
	return (1);
}

int	is_xyz(char *str)
{
	char	**parts;

	parts = ft_split(str, ',');
	if (splitsize(parts) != 3)
	{
		free_split(parts);
		return (0);
	}
	if (!isdouble(parts[0]) || !isdouble(parts[1]) || !isdouble(parts[2]))
	{
		free_split(parts);
		return (0);
	}
	free_split(parts);
	return (1);
}

int	checkambient(char **parts)
{
	if (splitsize(parts) != 3)
	{
		write(2, "Error\nToo little information for ambient lighting\n", 50);
		return (0);
	}
	if (!isdouble(parts[1]))
	{
		write(2, "Error\nIncorrect lighting ratio for ambient lighting\n", 52);
		return (0);
	}
	if (!is_colour(parts[2]))
	{
		write(2, "Error\nIncorrect color for ambient lighting\n", 43);
		return (0);
	}
	return (1);
}
