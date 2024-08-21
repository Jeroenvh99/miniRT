/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:43 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/21 18:25:17 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// objectinfo[0] = hit_point, objectinfo[1] = normal,
// objectinfo[2] = viewdirection

void	spot_colour(t_lighting **spots, t_XYZ objectinfo[3], t_colour *res)
{
	t_colour	res_diffuse;
	t_colour	res_spec;
	int			i;
	t_XYZ		light_dir;

	i = 0;
	while (spots[i])
	{
		if(shadow_checker(ray, rt, x, y, id) == 0)
		{
			light_dir = vec_subtraction(spots[i]->direction, hit_point);
			norm_vec(&light_dir);
			colours[1] = diffuse_lighting(spots[i], &light_dir, &normal);
			colours[2] = specular_lighting(spots[i], &light_dir, &normal,
					&viewdirection);
			colours[0].red = fmin(255, colours[0].red + colours[1].red
					+ colours[2].red);
			colours[0].green = fmin(255, colours[0].green + colours[1].green
					+ colours[2].green);
			colours[0].blue = fmin(255, colours[0].blue + colours[1].blue
					+ colours[2].blue);
		}
		++i;
	}
}

void	colour_3d_object(t_rt *rt, t_colour_3d_object_info *info, int coordinate[2], double t)
{
	t_colour	res;
	t_XYZ		objectinfo[3];
	t_lighting	**spots;

	res = ambient_lighting(&rt->scene->amb, info->colour);
	spots = rt->scene->lighting.array;
	objectinfo[0] = vec_addition(info->ray.origin, vec_multiplication(t, info->ray.dir));
	objectinfo[1] = vec_subtraction(objectinfo[0], *info->centre);
	norm_vec(&objectinfo[1]);
	objectinfo[2] = vec_multiplication(-1, info->ray.dir);
	norm_vec(&objectinfo[2]);
	spot_colour(spots, objectinfo, &res);
	if (t < rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist)
	{
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist = t;
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].colour
			= pack_colour(&res);
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].elemid = info->id;
	}
}

void	colour_2d_object(t_rt *rt, t_colour_2d_object_info *info, int coordinate[2], double t)
{
	t_colour	res;
	t_XYZ		objectinfo[3];
	t_lighting	**spots;

	objectinfo[0] = vec_addition(info->ray.origin, vec_multiplication(t, info->ray.dir));
	objectinfo[1] = *info->normal;
	objectinfo[2] = vec_multiplication(-1, info->ray.dir);
	norm_vec(&objectinfo[2]);
	res = ambient_lighting(&rt->scene->amb, info->colour);
	spots = rt->scene->lighting.array;
	spot_colour(spots, objectinfo, &res);
	if (t < rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist)
	{
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist = t;
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].colour
			= pack_colour(&res);
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].elemid = info->id;
	}
}
