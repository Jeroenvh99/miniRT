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
    double  inter;
    double  denominator;
    t_XYZ   diff;
	double	fourth;
	double	t;
	double	n;
	double	res;
	t_XYZ	int_point;

    denominator = dot_vec(ray->dir, plane.normal); 
    if (fabs(denominator) < 1e-10)
        return(-1.0);
    diff = vec_subtraction(plane.point, ray->origin);
	norm_vec(&diff);
    inter = dot_vec(diff, plane.normal) / denominator;
	if (inter < 0)
		return (-1.0);

	fourth = plane.normal.x * plane.point.x + plane.normal.y * plane.point.y + plane.normal.z * plane.point.z;
	n = ray->origin.x * plane.normal.x + ray->origin.y * plane.normal.y + ray->origin.z * plane.normal.z;
	t = plane.normal.x * ray->dir.x + plane.normal.y * ray->dir.y + plane.normal.z * ray->dir.z;
	fourth -= n;
	res = (fourth / t);
	int_point.x = ray->origin.x + ray->dir.x * res;
	int_point.y = ray->origin.y + ray->dir.y * res;
	int_point.z = ray->origin.z + ray->dir.z * res;
	// printf("%f\n", (0.5 * 1280) / tan(35));
	// printf("%f\n", int_point.y);
	// printf("%f\n", dot_vec(vec_subtraction(ray->origin, int_point), vector(0, 1, 0)));
    // printf("%f\n", inter);
    return (int_point.y - ray->origin.y);
}

void	draw_plane(t_rt *rt, t_geometry *geom)
{
	int		x;
	int		y;
	int		j;
	double	t;
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
			}*/
			t = hit_plane(*((t_plane *)geom->elem), &ray);
			if (t >= 0)
			{
				if (t < rt->pixeldata[y * rt->width + x].dist)
				{
					rt->pixeldata[y * rt->width + x].dist = t;
					rt->pixeldata[y * rt->width + x].colour = pack_colour(&((t_plane *)geom->elem)->colour);
				}
				// printf("%f\n", hit_plane(*((t_plane *)geom->elem), &ray));
				geom->screencoords[j].x = x;
				geom->screencoords[j].y = y;
				++j;
			}
			x++;
		}
		y++;
	}
}