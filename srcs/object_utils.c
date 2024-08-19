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

void	colour_object(t_rt *rt, t_ray *ray, t_colour *colour, t_XYZ *centre, int x, int y, double t, int id)
{
	t_colour	res_colour;
	int			i;
	t_XYZ		hit_point;
	t_XYZ		normal;
	t_XYZ		viewdirection;
	t_lighting	**spots;
	t_XYZ		light_dir;
	t_colour	res_diffuse;
	t_colour	res_spec;

	res_colour = ambient_lighting(&rt->scene->amb, colour);
	spots = rt->scene->lighting.array;
	i = 0;
	while (spots[i])
	{
		hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
		normal = vec_subtraction(hit_point, *centre);
		norm_vec(&normal);
		light_dir = vec_subtraction(spots[i]->direction, hit_point);
		norm_vec(&light_dir);
		res_diffuse = diffuse_lighting(spots[i], &light_dir, &normal);
		res_spec = specular_lighting(spots[i], &light_dir, &normal,
				&viewdirection);
		res_colour.red = fmin(255, res_colour.red + res_diffuse.red
				+ res_spec.red);
		res_colour.green = fmin(255, res_colour.green + res_diffuse.green
				+ res_spec.green);
		res_colour.blue = fmin(255, res_colour.blue + res_diffuse.blue
				+ res_spec.blue);
		++i;
	}
	res_colour.transparency = 255;
	if (t < rt->pixeldata[y * rt->width + x].dist)
	{
		rt->pixeldata[y * rt->width + x].dist = t;
		rt->pixeldata[y * rt->width + x].colour = pack_colour(&res_colour);
		rt->pixeldata[y * rt->width + x].elemid = id;
	}
}