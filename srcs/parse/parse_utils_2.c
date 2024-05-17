/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 14:30:09 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/03/20 13:46:57 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>

int	splitsize(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		++i;
	return (i);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		++i;
	}
	free(arr);
	arr = NULL;
}

void	**list_to_array(t_list *list)
{
	void	**res;
	t_list	*tmp;
	int		i;

	i = 0;
	res = malloc((ft_lstsize(list) + 1) * sizeof(void *));
	while (list)
	{
		res[i] = list->content;
		++i;
		tmp = list->next;
		free(list);
		list = tmp;
	}
	res[i] = NULL;
	return (res);
}

int	geomsize(t_geometry **geom)
{
	int	i;

	i = 0;
	while (geom[i])
	{
		++i;
	}
	return (i);
}

void	build_arrays(t_scene *scene)
{
	scene->lighting.array = (t_lighting **)list_to_array(scene->lighting.list);
	scene->geometry.array = (t_geometry **)list_to_array(scene->geometry.list);
	scene->geomsize = geomsize(scene->geometry.array);
}
