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

void	hit_plane(t_plane *plane, t_ray *ray, t_rt *rt, int x, int y, int id)
{
	double		denominator;
	t_XYZ		diff;
	double		t;
	t_colour	res_ambient;
	t_colour	res_colour;
	int			i;
	t_XYZ		hit_point;
	t_XYZ		viewdirection;
	t_lighting	**spots;
	t_XYZ		light_dir;
	t_colour	res_diffuse;
	t_colour	res_spec;

	denominator = dot_vec(ray->dir, plane->normal);
	if (fabs(denominator) < 1e-10)
		return ;
	diff = vec_subtraction(plane->point, ray->origin);
	t = dot_vec(diff, plane->normal) / denominator;
	if (t >= 0)
	{
		hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
		viewdirection = vec_multiplication(-1, ray->dir);
		norm_vec(&viewdirection);
		res_ambient = ambient_lighting(&rt->scene->amb, &plane->colour);
		res_colour.red = fmin(255, res_ambient.red);
		res_colour.green = fmin(255, res_ambient.green);
		res_colour.blue = fmin(255, res_ambient.blue);
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
		}
	}
}

void	draw_plane(t_rt *rt, t_geometry *geom, int id)
{
	int		x;
	int		y;
	t_ray	ray;
	t_plane	transformedplane;

	transformedplane.point = base_transform(rt->camtransform, &((t_plane *)geom->elem)->point);
	transformedplane.normal = base_transform(rt->camtransform, &((t_plane *)geom->elem)->normal);
	transformedplane.colour = ((t_plane *)geom->elem)->colour;
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray_launcher(rt, &ray, x, y);
			hit_plane(&transformedplane, &ray, rt, x, y, id);
			x++;
		}
		y++;
	}
}
