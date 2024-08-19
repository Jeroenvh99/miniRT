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

static t_colour	ambient_lighting(t_ambient *ambient, t_plane *plane)
{
	t_colour	res_ambient;

	res_ambient.red = ((ambient->intensity * ambient->colour.red
				+ plane->colour.red) / 255);
	res_ambient.green = ((ambient->intensity * ambient->colour.green
				+ plane->colour.green) / 255);
	res_ambient.blue = ((ambient->intensity * ambient->colour.blue
				+ plane->colour.blue) / 255);
	return (res_ambient);
}

// static t_colour	diffuse_lighting(t_lighting *light, t_XYZ dir, t_XYZ normal)
// {
// 	double	diffuse_factor;
// 	t_colour	res_diffuse;

// 	diffuse_factor = fmax(dot_vec(normal, dir), 0.0);
// 	res_diffuse.red = (light->brightness * diffuse_factor * light->colour.red);
// 	res_diffuse.green = (light->brightness * diffuse_factor * light->colour.green);
// 	res_diffuse.blue = (light->brightness * diffuse_factor * light->colour.blue);
// 	return (res_diffuse);
// }

// static t_colour	specular_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal,
// 		t_XYZ *viewdirection)
// {
// 	t_XYZ reflection;
// 	double spec;
// 	t_colour	res_spec;

// 	reflection = vec_subtraction(vec_multiplication(2 * dot_vec(*normal, *dir),
// 				*normal), *dir);
// 	spec = pow(fmax(dot_vec(reflection, *viewdirection), 0.0), SHINE);
// 	res_spec.red = (light->brightness * spec * light->colour.red);
// 	res_spec.green = (light->brightness * spec * light->colour.green);
// 	res_spec.blue = (light->brightness * spec * light->colour.blue);
// 	return (res_spec);
// }

void  hit_plane(t_plane *plane, t_ray *ray, t_rt *rt, int x, int y, int id)
{
    double  denominator;
    t_XYZ   diff;
	double	t;
	t_colour	res_ambient;
	t_colour	res_colour;
	// int			i;
	t_XYZ		hit_point;
	t_XYZ		viewdirection;
	// t_lighting	**spots;
	// t_XYZ		light_dir;
	// t_colour	res_diffuse;
	// t_colour	res_spec;

    denominator = dot_vec(ray->dir, plane->normal); 
    if (fabs(denominator) < 1e-10)
        return;
    diff = vec_subtraction(plane->point, ray->origin);
    t = dot_vec(diff, plane->normal) / denominator;
	if (t >= 0)
	{
		hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
		viewdirection = vec_multiplication(-1, ray->dir);
		norm_vec(&viewdirection);
		res_ambient = ambient_lighting(&rt->scene->amb, plane);
		res_colour.red = fmin(255, 255 * res_ambient.red);
		res_colour.green = fmin(255, 255 * res_ambient.green);
		res_colour.blue = fmin(255, 255 * res_ambient.blue);
		// spots = rt->scene->lighting.array;
		// i = 0;
		// while (spots[i])
		// {
		// 	light_dir = vec_subtraction(spots[i]->direction, hit_point);
		// 	norm_vec(&light_dir);
		// 	res_diffuse = diffuse_lighting(spots[i], light_dir, normal);
		// 	res_spec = specular_lighting(spots[i], &light_dir, &plane->normal,
		// 			&viewdirection);
		// 	res_colour.red = fmin(255, res_colour.red + res_diffuse.red
		// 			+ res_spec.red);
		// 	res_colour.green = fmin(255, res_colour.green + res_diffuse.green
		// 			+ res_spec.green);
		// 	res_colour.blue = fmin(255, res_colour.blue + res_diffuse.blue
		// 			+ res_spec.blue);
		// 	++i;
		// }
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
			hit_plane(&transformedplane, &ray, rt, x, y, id);
			x++;
		}
		y++;
	}
}