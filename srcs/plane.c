/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:32:04 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/03 16:52:48 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math.h"
#include <stdio.h>

double  hit_plane(t_plane plane, t_ray *ray)
{
    double  inter;
    double  res;
    t_XYZ   diff;

    inter = dot_vec(ray->dir, plane.normal);
    if (fabs(inter) < 1e-20)
        return(-1.0);
    diff = vec_subtraction(plane.point, ray->origin);
    res = dot_vec(diff, plane.normal) / inter;
    if (res < 0)
        return (-1.0);
    return (res);
}

void	draw_plane(t_rt *rt, t_geometry *geom)
{
	double	x;
	double	y;
	int		j;
	t_ray	ray;
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
			}
			geom->screencoords[(int)(x + (y * rt->width))].x = 0;
			geom->screencoords[(int)(x + (y * rt->width))].x = 0;*/
			if (hit_plane(*((t_plane *)geom->elem), &ray) >= 0)
			{
				geom->screencoords[j].x = x;
				geom->screencoords[j].y = y;
				++j;
				mlx_put_pixel(rt->image, x, y, pack_colour(&((t_plane *)geom->elem)->colour));
			}
			x++;
		}
		y++;
	}
}