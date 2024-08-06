/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:32:04 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/04 17:08:36 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math.h"
#include <stdio.h>

double  hit_plane(t_plane plane, t_ray *ray)
{
    double  denominator;
    t_XYZ   diff;

    denominator = dot_vec(ray->dir, plane.normal); 
    if (fabs(denominator) < 1e-10)
        return(-1.0);
    diff = vec_subtraction(plane.point, ray->origin);
    return (dot_vec(diff, plane.normal) / denominator);
}

void	draw_plane(t_rt *rt, t_geometry *geom)
{
	int		x;
	int		y;
	int		j;
	double	t;
	t_ray	ray;
	t_plane	transformedplane;
	// t_colour	tempcolour;
	// t_colour	colour;
	// t_plane     plane;

	j = 0;
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray = ray_launcher(rt, ray, x, y);
			/*t_lighting **spots;
			spots = rt->scene->lighting.array;
			colour.red = colour.green = colour.blue = colour.transparency = 0;
			int i = 0;
			while (spots[i])
			{
				colour = pixel_colour(&transformedsphere, &ray, rt->scene->amb, *spots[i], SHINE);
				++i;
			}*/
			transformedplane.point = base_transform(rt->camtransform, ((t_plane *)geom->elem)->point);
			transformedplane.normal = base_transform(rt->camtransform, ((t_plane *)geom->elem)->normal);
			transformedplane.colour = ((t_plane *)geom->elem)->colour;
			t = hit_plane(transformedplane, &ray);
			if (t >= 0)
			{
				if (t < rt->pixeldata[y * rt->width + x].dist)
				{
					rt->pixeldata[y * rt->width + x].dist = t;
					rt->pixeldata[y * rt->width + x].colour = pack_colour(&((t_plane *)geom->elem)->colour);
				}
				geom->screencoords[j].x = x;
				geom->screencoords[j].y = y;
				++j;
			}
			x++;
		}
		y++;
	}
}