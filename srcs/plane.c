/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:32:04 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/21 19:32:59 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//coordinate[0] = x, coordinate[1] = y

double	hit_plane(t_plane *plane, t_ray *ray)
{
	double	denominator;
	t_XYZ	diff;
	double	t;

	denominator = dot_vec(&ray->dir, &plane->normal);
	if (fabs(denominator) < 1e-10)
		return (-1.0);
	diff = vec_subtraction(plane->point, ray->origin);
	t = dot_vec(&diff, &plane->normal) / denominator;
	return (t);
}

void	draw_plane(t_rt *rt, t_geometry *geom, int id)
{
	int						coordinate[2];
	double					t;
	t_plane					transformedplane;
	t_colour_2d_object_info	info;

	transformedplane.point = base_transform(rt->camtransform,
			&((t_plane *)geom->elem)->point);
	transformedplane.normal = base_transform(rt->camtransform,
			&((t_plane *)geom->elem)->normal);
	transformedplane.colour = ((t_plane *)geom->elem)->colour;
	coordinate[1] = 0;
	info.id = id;
	info.colour = &transformedplane.colour;
	info.normal = &transformedplane.normal;
	while (coordinate[1] < rt->height)
	{
		coordinate[0] = 0;
		while (coordinate[0] < rt->width)
		{
			ray_launcher(rt, &info.ray, coordinate[0], coordinate[1]);
			t = hit_plane(&transformedplane, &info.ray);
			if (t > 0)
			{
				colour_2d_object(rt, &info, coordinate, t);
			}
			coordinate[0]++;
		}
		coordinate[1]++;
	}
}
