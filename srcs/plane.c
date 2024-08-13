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
#include <stdio.h>

double  hit_plane(t_plane *plane, t_ray *ray)
{
    double  denominator;
    t_XYZ   diff;

    denominator = dot_vec(ray->dir, plane->normal); 
    if (fabs(denominator) < 1e-10)
        return(-1.0);
    diff = vec_subtraction(plane->point, ray->origin);
    return (dot_vec(diff, plane->normal) / denominator);
}

void	draw_plane(t_rt *rt, t_geometry *geom, int id)
{
	int		x;
	int		y;
	double	t;
	t_ray	ray;
	t_plane	transformedplane;

	transformedplane.point = base_transform(rt->camtransform, ((t_plane *)geom->elem)->point);
	transformedplane.normal = base_transform(rt->camtransform, ((t_plane *)geom->elem)->normal);
	transformedplane.colour = ((t_plane *)geom->elem)->colour;
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray_launcher(rt, &ray, x, y);
			t = hit_plane(&transformedplane, &ray);
			if (t >= 0)
			{
				if (t < rt->pixeldata[y * rt->width + x].dist)
				{
					rt->pixeldata[y * rt->width + x].dist = t;
					rt->pixeldata[y * rt->width + x].colour = pack_colour(&transformedplane.colour);
					rt->pixeldata[y * rt->width + x].elemid = id;
				}
			}
			x++;
		}
		y++;
	}
}