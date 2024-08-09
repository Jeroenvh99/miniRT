/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:22:01 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/17 20:02:48 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdlib.h>
#include <unistd.h>

int	checkfilename(char *file)
{
	file = ft_strrchr(file, '.');
	if (file && ft_strncmp(file, ".rt", 4) == 0)
		return (1);
	write(2, "Error\nIncorrect inputfile, use the .rt extension\n", 49);
	return (0);
}

t_scene	*initscene(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit(1);
	scene->isresized = 0;
	scene->amb.intensity = 101;
	scene->cam.fov = 181;
	scene->lighting.list = NULL;
	scene->geometry.list = NULL;
	return (scene);
}

void	free_geom(void *geometry)
{
	t_geometry	*geom;

	geom = (t_geometry *)geometry;
	free(geom->elem);
	free(geom);
}

void	free_arr(void **arr, void (*del)(void *))
{
	int	i;

	i = 0;
	while (arr[i])
	{
		(*del)(arr[i]);
		arr[i] = NULL;
		++i;
	}
	free(arr);
	arr = NULL;
}

void	free_scene(t_scene *scene, int isarr)
{
	if (isarr)
	{
		free_arr((void **)scene->lighting.array, free);
		free_arr((void **)scene->geometry.array, free_geom);
	}
	else
	{
		ft_lstclear(&scene->lighting.list, free);
		ft_lstclear(&scene->geometry.list, free_geom);
	}
	free(scene);
}

int	spherecollision(t_XYZ *lightpos, t_sphere *sphere)
{
	return (distance(lightpos, &sphere->centre) == sphere->radius);
}

int	planecollission(t_XYZ *lightpos, t_plane *plane)
{
	double	right;
	double	left;

	if (same_point(lightpos, &plane->point))
	{
		return (1);
	}
	right = (lightpos->x * plane->normal.x + lightpos->y * plane->normal.y
			+ lightpos->z * plane->normal.z);
	left = dot_vec(plane->point, plane->normal);
	if (right >= left * 0.99 && right <= left * 1.01)
	{
		return (1);
	}
	return (0);
}

int	cylindercollission(t_XYZ *lightpos, t_cylinder *cylinder)
{
	t_plane	cap1;
	t_plane	cap2;
	double	halfheight;

	if (distancetoline(lightpos, &cylinder->centre,
			&cylinder->axis) == cylinder->radius)
	{
		return (1);
	}
	halfheight = cylinder->height * 0.5;
	cap1.normal = cylinder->axis;
	cap1.point = vector(cylinder->centre.x + (cylinder->axis.x * halfheight),
			cylinder->centre.y + (cylinder->axis.y * halfheight),
			cylinder->centre.z + (cylinder->axis.z * halfheight));
	cap2.normal = cylinder->axis;
	cap2.point = vector(cylinder->centre.x - (cylinder->axis.x * halfheight),
			cylinder->centre.y - (cylinder->axis.y * halfheight),
			cylinder->centre.z - (cylinder->axis.z * halfheight));
	if (distancetoline(lightpos, &cylinder->centre,
			&cylinder->axis) <= cylinder->radius && (planecollission(lightpos,
				&cap1) || planecollission(lightpos, &cap2)))
	{
		return (1);
	}
	return (0);
}

int	checklightcollision(t_scene *scene)
{
	t_list		*lights;
	t_lighting	*spot;
	t_list		*geometry;
	t_geometry	*geom;

	lights = scene->lighting.list;
	while (lights)
	{
		spot = (t_lighting *)lights->content;
		geometry = scene->geometry.list;
		while (geometry)
		{
			geom = (t_geometry *)geometry->content;
			if (geom->elemtype == 1 && spherecollision(&spot->direction,
					(t_sphere *)geom->elem))
			{
				return (1);
			}
			else if (geom->elemtype == 2 && planecollission(&spot->direction,
					(t_plane *)geom->elem))
			{
				return (1);
			}
			else if (geom->elemtype == 3 && cylindercollission(&spot->direction,
					(t_cylinder *)geom->elem))
			{
				return (1);
			}
			geometry = geometry->next;
		}
		lights = lights->next;
	}
	return (0);
}

int	checkscene(t_scene *scene)
{
	if (scene->amb.intensity == 101)
	{
		write(2, "Error\nThe scene doesn't contain ambient lighting\n", 49);
		return (0);
	}
	if (scene->cam.fov > 180)
	{
		write(2, "Error\nThe scene doesn't contain a camera\n", 41);
		return (0);
	}
	if (ft_lstsize(scene->lighting.list) == 0)
	{
		write(2, "Error\nThe scene doesn't contain any lights\n", 43);
		return (0);
	}
	if (ft_lstsize(scene->geometry.list) == 0)
	{
		write(2, "Error\nThe scene doesn't contain any elements\n", 44);
		return (0);
	}
	if (checklightcollision(scene))
	{
		write(2, "one of the lights lies in an object\n", 36);
		return (0);
	}
	return (1);
}
