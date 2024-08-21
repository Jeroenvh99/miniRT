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

void	colour_3d_object(t_rt *rt, t_ray *ray, t_colour *colour, t_XYZ *centre, int x, int y, double t, int id)
{
	t_colour	colours[3];
	int			i;
	t_XYZ		hit_point;
	t_XYZ		normal;
	t_XYZ		viewdirection;
	t_lighting	**spots;
	t_XYZ		light_dir;

	colours[0] = ambient_lighting(&rt->scene->amb, colour);
	spots = rt->scene->lighting.array;
	i = 0;
	hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
	normal = vec_subtraction(hit_point, *centre);
	norm_vec(&normal);
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
	if (t < rt->pixeldata[y * rt->width + x].dist)
	{
		rt->pixeldata[y * rt->width + x].dist = t;
		rt->pixeldata[y * rt->width + x].colour = pack_colour(&colours[0]);
		rt->pixeldata[y * rt->width + x].elemid = id;
	}
}
