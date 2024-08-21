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

//coordinate[0] = x, coordinate[1] = y

void	hit_plane(t_plane *plane, t_colour_2d_object_info *info, t_rt *rt, int coordinate[2])
{
	double	denominator;
	t_XYZ	diff;
	double	t;

	denominator = dot_vec(&info->ray.dir, info->normal);
	if (fabs(denominator) < 1e-10)
		return ;
	diff = vec_subtraction(plane->point, info->ray.origin);
	t = dot_vec(&diff, &plane->normal) / denominator;
	if (t >= 0)
	{
		colour_2d_object(rt, info, coordinate, t);
	}
}

void	draw_plane(t_rt *rt, t_geometry *geom, int id)
{
	int						coordinate[2];
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
			hit_plane(&transformedplane, &info, rt, coordinate);
			coordinate[0]++;
		}
		coordinate[1]++;
	}
}
