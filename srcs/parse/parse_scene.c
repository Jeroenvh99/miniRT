/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:16:25 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/17 20:00:27 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parse.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	parseambient(t_scene *scene, char *line)
{
	char	**parts;

	if (scene->amb.intensity <= 100)
	{
		write(2, "Error\nAmbient lighting is already defined\n", 42);
		return (0);
	}
	parts = ft_split(line, ' ');
	if (!checkambient(parts))
	{
		free_split(parts);
		return (0);
	}
	scene->amb.intensity = ft_atof(parts[1]);
	parse_colour(parts[2], &scene->amb.colour);
	free_split(parts);
	return (1);
}

static int	parsecamera(t_scene *scene, char *line)
{
	char	**parts;

	if (scene->cam.fov <= 180)
	{
		write(2, "Error\nThis scene already has a camera\n", 38);
		return (0);
	}
	parts = ft_split(line, ' ');
	if (!checkcamera(parts))
	{
		free_split(parts);
		return (0);
	}
	parse_xyz(parts[1], &scene->cam.pos);
	parse_xyz(parts[2], &scene->cam.viewdirection);
	scene->cam.fov = ft_atoi(parts[3]);
	free_split(parts);
	return (1);
}

static int	parselight(t_scene *scene, char *line)
{
	t_lighting	*spot;
	char		**parts;

	parts = ft_split(line, ' ');
	spot = malloc(sizeof(t_lighting));
	if (!spot || !checklight(parts))
	{
		free_split(parts);
		return (0);
	}
	parse_xyz(parts[1], &spot->direction);
	spot->brightness = ft_atof(parts[2]);
	parse_colour(parts[3], &spot->colour);
	ft_lstadd_back(&scene->lighting.list, ft_lstnew(spot));
	free_split(parts);
	return (1);
}

static int	parseline(t_scene *scene, char *line)
{
	int					i;
	static const char	*rt_elements[N_ELEMENTS] = {"A", "C", "L", "sp", "pl",
		"cy"};
	t_parsef const		parsef[N_ELEMENTS] = {parseambient, parsecamera,
		parselight, parsesphere, parseplane, parsecylinder};

	i = 0;
	while (i < N_ELEMENTS)
	{
		if (!ft_strncmp(line, rt_elements[i], ft_strchr(line, ' ') - line))
		{
			return (parsef[i](scene, line));
		}
		++i;
	}
	write(2, "Error\nUnrecognized line in input\n", 33);
	return (0);
}

void	readscene(t_scene *scene, char *scenefile)
{
	char	*line;
	int		fd;

	if (!checkfilename(scenefile))
		exit(1);
	scene->filename = scenefile;
	fd = open(scenefile, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (*(skipspace(line)) != '\0')
		{
			tabtospace(line);
			if (parseline(scene, line) == 0)
				exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
