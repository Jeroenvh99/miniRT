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
	/*if (t >= 0)
	{
		hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
		viewdirection = vec_multiplication(-1, ray->dir);
		norm_vec(&viewdirection);
		res_colour = ambient_lighting(&rt->scene->amb, &plane->colour);
		spots = rt->scene->lighting.array;
		i = 0;
		while (spots[i])
		{
			light_dir = vec_subtraction(spots[i]->direction, hit_point);
			norm_vec(&light_dir);
			res_diffuse = diffuse_lighting(spots[i], &light_dir, &plane->normal);
			res_spec = specular_lighting(spots[i], &light_dir, &plane->normal,
					&viewdirection);
			res_colour.red = fmin(255, res_colour.red + res_diffuse.red
					+ res_spec.red);
			res_colour.green = fmin(255, res_colour.green + res_diffuse.green
					+ res_spec.green);
			res_colour.blue = fmin(255, res_colour.blue + res_diffuse.blue
					+ res_spec.blue);
			++i;
		}
		if (t < rt->pixeldata[y * rt->width + x].dist)
		{
			rt->pixeldata[y * rt->width + x].dist = t;
			rt->pixeldata[y * rt->width + x].colour = pack_colour(&res_colour);
			rt->pixeldata[y * rt->width + x].elemid = id;
		}*/
	if (t >= 0)
		return (t);
	return (-1.0);
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
