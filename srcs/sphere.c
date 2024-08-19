/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:04:50 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/09 15:35:43 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_sphere sphere, t_ray *ray)
{
	double	a;
	double	b;
	double	delta;
	double	sol1;
	double	sol2;
	t_XYZ	diff;

	diff = vec_subtraction(ray->origin, sphere.centre);
	a = dot_vec(ray->dir, ray->dir);
	b = 2 * dot_vec(diff, ray->dir);
	delta = b * b - 4 * a * (dot_vec(diff, diff) - sphere.radius
			* sphere.radius);
	if (delta < 0)
		return (-1.0);
	sol1 = (-b - sqrt(delta)) / (2.0 * a);
	sol2 = (-b + sqrt(delta)) / (2.0 * a);
	if (sol1 > 0 && sol2 > 0)
	{
		return (fmin(sol1, sol2));
	}
	else if (sol1 > 0 || sol2 > 0)
		return (fmax(sol1, sol2));
	else
		return (-1.0);
}

void	pixel_colour(t_sphere *sphere, t_ray *ray, int x, int y, t_rt *rt, int id)
{
	t_colour	res_colour;
	double		t;
	int			i;
	t_XYZ		hit_point;
	t_XYZ		normal;
	t_XYZ		viewdirection;
	t_colour	res_ambient;
	t_lighting	**spots;
	t_XYZ		light_dir;
	t_colour	res_diffuse;
	t_colour	res_spec;

	t = hit_sphere(*sphere, ray);
	if (t > 0)
	{
		hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
		normal = vec_subtraction(hit_point, sphere->centre);
		norm_vec(&normal);
		viewdirection = vec_multiplication(-1, ray->dir);
		norm_vec(&viewdirection);
		res_ambient = ambient_lighting(&rt->scene->amb, &sphere->colour);
		res_colour.red = fmin(255, res_ambient.red);
		res_colour.green = fmin(255, res_ambient.green);
		res_colour.blue = fmin(255, res_ambient.blue);
		spots = rt->scene->lighting.array;
		i = 0;
		while (spots[i])
		{
			light_dir = vec_subtraction(spots[i]->direction, hit_point);
			norm_vec(&light_dir);
			res_diffuse = diffuse_lighting(spots[i], &light_dir, &normal);
			res_spec = specular_lighting(spots[i], &light_dir, &normal,
					&viewdirection);
			res_colour.red = fmin(255, res_colour.red + res_diffuse.red
					+ res_spec.red);
			res_colour.green = fmin(255, res_colour.green + res_diffuse.green
					+ res_spec.green);
			res_colour.blue = fmin(255, res_colour.blue + res_diffuse.blue
					+ res_spec.blue);
			++i;
		}
		res_colour.transparency = 255;
		if (t < rt->pixeldata[y * rt->width + x].dist)
		{
			rt->pixeldata[y * rt->width + x].dist = t;
			rt->pixeldata[y * rt->width + x].colour = pack_colour(&res_colour);
			rt->pixeldata[y * rt->width + x].elemid = id;
		}
	}
}

uint32_t	pack_colour(t_colour *colour)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)colour->red;
	g = (unsigned int)colour->green;
	b = (unsigned int)colour->blue;
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	draw_sphere(t_rt *rt, t_geometry *geom, int id)
{
	int			x;
	int			y;
	t_ray		ray;
	t_sphere	transformedsphere;

	transformedsphere.centre = base_transform(rt->camtransform,
			((t_sphere *)geom->elem)->centre);
	transformedsphere.radius = ((t_sphere *)geom->elem)->radius;
	transformedsphere.colour = ((t_sphere *)geom->elem)->colour;
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray_launcher(rt, &ray, x, y);
			pixel_colour(&transformedsphere, &ray, x, y, rt, id);
			x++;
		}
		y++;
	}
}
