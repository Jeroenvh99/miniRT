/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:43 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/19 15:34:25 by sjeddi           ###   ########.fr       */
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
		light_dir = vec_subtraction(spots[i]->direction, objectinfo[0]);
		norm_vec(&light_dir);
		res_diffuse = diffuse_lighting(spots[i], &light_dir, &objectinfo[1]);
		res_spec = specular_lighting(spots[i], &light_dir, &objectinfo[1],
				&objectinfo[2]);
		res->red = fmin(255, res->red + res_diffuse.red
				+ res_spec.red);
		res->green = fmin(255, res->green + res_diffuse.green
				+ res_spec.green);
		res->blue = fmin(255, res->blue + res_diffuse.blue
				+ res_spec.blue);
		++i;
	}
}

void	colour_3d_object(t_rt *rt, t_ray *ray, t_colour *colour, t_XYZ *centre, int coordinate[2], double t, int id)
{
	t_colour	res;
	t_XYZ		objectinfo[3];
	t_lighting	**spots;

	res = ambient_lighting(&rt->scene->amb, colour);
	spots = rt->scene->lighting.array;
	objectinfo[0] = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
	objectinfo[1] = vec_subtraction(objectinfo[0], *centre);
	norm_vec(&objectinfo[1]);
	objectinfo[2] = vec_multiplication(-1, ray->dir);
	norm_vec(&objectinfo[2]);
	spot_colour(spots, objectinfo, &res);
	if (t < rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist)
	{
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist = t;
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].colour
			= pack_colour(&res);
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].elemid = id;
	}
}

void	colour_2d_object(t_rt *rt, t_ray *ray, t_colour *colour, t_XYZ *normal, int coordinate[2], double t, int id)
{
	t_colour	res;
	t_XYZ		objectinfo[3];
	t_lighting	**spots;

	objectinfo[0] = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
	objectinfo[1] = *normal;
	objectinfo[2] = vec_multiplication(-1, ray->dir);
	norm_vec(&objectinfo[2]);
	res = ambient_lighting(&rt->scene->amb, colour);
	spots = rt->scene->lighting.array;
	spot_colour(spots, objectinfo, &res);
	if (t < rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist)
	{
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].dist = t;
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].colour
			= pack_colour(&res);
		rt->pixeldata[coordinate[1] * rt->width + coordinate[0]].elemid = id;
	}
}
