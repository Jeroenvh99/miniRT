/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:43 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/06 14:23:21 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

/*int	hit_cylinder(t_cylinder cylinder, t_ray ray, int *output)
{
	t_XYZ	diff;
	t_XYZ	point_disc;
	t_XYZ	vec_disc;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol1;
	double	sol2;
	double	holder;
	double	inter1;
	double	inter2;
	double	closest_inter;
	double	top_disc;
	double	disc;

	diff = vec_subtraction(ray.origin, cylinder.centre);
	a = dot_vec(ray.dir, ray.dir) - dot_vec(ray.dir, cylinder.axis) * dot_vec(ray.dir, cylinder.axis);
	b = 2 * (dot_vec(ray.dir, diff) - dot_vec(ray.dir, cylinder.axis) * dot_vec(diff, cylinder.axis));
	c = dot_vec(diff, diff) - dot_vec(diff, cylinder.axis) * dot_vec(diff, cylinder.axis) - cylinder.radius * cylinder.radius;
	delta = b * b - 4 * a * c;
	closest_inter = -1;
	if (delta >= 0)
	{
		sol1 = (-b - sqrt(delta)) / (2 * a);
		sol2 = (-b + sqrt(delta)) / (2 * a);
		if (sol1 > sol2)
		{
			holder = sol1;
			sol1 = sol2;
			sol2 = holder;
		}
		inter1 = dot_vec(ray.dir, cylinder.axis) * sol1 + dot_vec(diff, cylinder.axis);
		inter2 = dot_vec(ray.dir, cylinder.axis) * sol2 + dot_vec(diff, cylinder.axis);
		if ((inter1 >= 0 && inter1 <= cylinder.height) && (sol1 >= 0 && (closest_inter == -1 || sol1 < closest_inter)))
		{
			closest_inter = sol1;
		}
		if ((inter2 >= 0 && inter2 <= cylinder.height) && (sol2 >= 0 && (closest_inter == -1 || sol2 < closest_inter)))
		{
			closest_inter = sol2;
		}
	}
	disc = -dot_vec(diff, cylinder.axis) / dot_vec(ray.dir, cylinder.axis);
	if (disc >= 0)
	{
		point_disc = vec_addition(ray.origin, vec_multiplication(disc, ray.dir));
		vec_disc = vec_subtraction(point_disc, cylinder.centre);
		if (dot_vec(vec_disc, vec_disc) <= cylinder.radius * cylinder.radius && (closest_inter == -1) || disc < closest_inter)
		{
			closest_inter = disc;
		}
	}
	disc = (cylinder.height - dot_vec(diff, cylinder.axis)) / dot_vec(ray.dir, cylinder.axis);
	if (disc >= 0)
	{
		point_disc = vec_addition(ray.origin, vec_multiplication(disc, ray.dir));
		vec_disc = vec_subtraction(point_disc, vec_addition(cylinder.centre, vec_multiplication(cylinder.height, cylinder.axis)));
		if (dot_vec(vec_disc, vec_disc) <= cylinder.radius * cylinder.radius && (closest_inter == -1) || disc < closest_inter)
		{
			closest_inter = disc;
		}
	}
	if (closest_inter != -1)
	{
		*output = closest_inter;
		return (1);
	}
	return (0);
}*/


// first thing's first: find 

/*t_colour	pixel_colour(t_cylinder *cylinder, t_ray *ray, t_ambient ambient, t_lighting light, double shininess)
{
	t_colour	res_colour;
	double t;
	t = hit_cylinder(*sphere, ray);
	if (t < 0)
		return ((t_colour){0, 0, 0, 0});
	else
	{
		t_XYZ hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
		t_XYZ	normal = vec_subtractionion(hit_point, sphere->centre);
		norm_vec(&normal);
		t_XYZ	light_dir = vec_subtractionion(light.direction, hit_point);
		norm_vec(&light_dir);
		t_XYZ	viewdirection = vec_multiplication(-1, ray->dir);
		norm_vec(&viewdirection);
		t_colour	res_ambient = ambient_lighting(ambient, *sphere);
		t_colour	res_diffuse = diffuse_lighting(light, light_dir, normal, *sphere);
		t_colour	res_spec = specular_lighting(light, light_dir, normal, viewdirection, shininess);
		res_colour.red = (unsigned int) fmin(255, res_ambient.red + res_diffuse.red + res_spec.red);
		res_colour.green = (unsigned int) fmin(255, res_ambient.green + res_diffuse.green + res_spec.green);
		res_colour.blue = (unsigned int) fmin(255, res_ambient.blue + res_diffuse.blue + res_spec.blue);
		res_colour.transparency = 255;
		return (res_colour);
	}
}*/

static t_colour	ambient_lighting(t_ambient *ambient, t_cylinder *cylinder)
{
	t_colour	res_ambient;

	res_ambient.red = ((ambient->intensity * ambient->colour.red
				+ cylinder->colour.red) / 255);
	res_ambient.green = ((ambient->intensity * ambient->colour.green
				+ cylinder->colour.green) / 255);
	res_ambient.blue = ((ambient->intensity * ambient->colour.blue
				+ cylinder->colour.blue) / 255);
	return (res_ambient);
}

static t_colour	diffuse_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal)
{
	double	diffuse_factor;
	t_colour	res_diffuse;

	diffuse_factor = fmax(dot_vec(*normal, *dir), 0.0);
	res_diffuse.red = (light->brightness * diffuse_factor * light->colour.red);
	res_diffuse.green = (light->brightness * diffuse_factor * light->colour.green);
	res_diffuse.blue = (light->brightness * diffuse_factor * light->colour.blue);
	return (res_diffuse);
}

static t_colour	specular_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal,
		t_XYZ *viewdirection)
{
	t_XYZ reflection;
	double spec;
	t_colour	res_spec;

	reflection = vec_subtraction(vec_multiplication(2 * dot_vec(*normal, *dir),
				*normal), *dir);
	spec = pow(fmax(dot_vec(reflection, *viewdirection), 0.0), SHINE);
	res_spec.red = (light->brightness * spec * light->colour.red);
	res_spec.green = (light->brightness * spec * light->colour.green);
	res_spec.blue = (light->brightness * spec * light->colour.blue);
	return (res_spec);
}

void	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_rt *rt, int x, int y, int id)
{
    t_XYZ diff;
    t_XYZ point_disc;
    t_XYZ vec_disc;
    double a;
    double b;
    double c;
    double delta;
    double sol1;
    double sol2;
    double holder;
    double inter1;
    double inter2;
    double closest_inter = -1; // Initialize closest_inter to -1
    double disc;
	double t;
	t_colour	res_colour;
	int			i;
	t_XYZ		hit_point;
	t_XYZ		normal;
	t_XYZ		viewdirection;
	t_colour	res_ambient;
	t_lighting	**spots;
	t_XYZ		light_dir;
	t_colour	res_diffuse;
	t_colour	res_spec;

    diff = vec_subtraction(ray->origin, cylinder->centre);
    a = dot_vec(ray->dir, ray->dir) - dot_vec(ray->dir, cylinder->axis) * dot_vec(ray->dir, cylinder->axis);
    b = 2 * (dot_vec(ray->dir, diff) - dot_vec(ray->dir, cylinder->axis) * dot_vec(diff, cylinder->axis));
    c = dot_vec(diff, diff) - dot_vec(diff, cylinder->axis) * dot_vec(diff, cylinder->axis) - cylinder->radius * cylinder->radius;
    delta = b * b - 4 * a * c;
    if (delta >= 0)
    {
        sol1 = (-b - sqrt(delta)) / (2 * a);
        sol2 = (-b + sqrt(delta)) / (2 * a);
        if (sol1 > sol2)
        {
            holder = sol1;
            sol1 = sol2;
            sol2 = holder;
        }
        inter1 = dot_vec(ray->dir, cylinder->axis) * sol1 + dot_vec(diff, cylinder->axis);
        inter2 = dot_vec(ray->dir, cylinder->axis) * sol2 + dot_vec(diff, cylinder->axis);
        if ((inter1 >= 0 && inter1 <= cylinder->height) && (sol1 >= 0 && (closest_inter == -1 || sol1 < closest_inter)))
        {
            closest_inter = sol1;
        }
        if ((inter2 >= 0 && inter2 <= cylinder->height) && (sol2 >= 0 && (closest_inter == -1 || sol2 < closest_inter)))
        {
            closest_inter = sol2;
        }
    }
    disc = -dot_vec(diff, cylinder->axis) / dot_vec(ray->dir, cylinder->axis);
    if (disc >= 0)
    {
        point_disc = vec_addition(ray->origin, vec_multiplication(disc, ray->dir));
        vec_disc = vec_subtraction(point_disc, cylinder->centre);
        if ((dot_vec(vec_disc, vec_disc) <= cylinder->radius * cylinder->radius) && (closest_inter == -1 || disc < closest_inter))
        {
            closest_inter = disc;
        }
    }
    disc = (cylinder->height - dot_vec(diff, cylinder->axis)) / dot_vec(ray->dir, cylinder->axis);
    if (disc >= 0)
    {
        point_disc = vec_addition(ray->origin, vec_multiplication(disc, ray->dir));
        vec_disc = vec_subtraction(point_disc, vec_addition(cylinder->centre, vec_multiplication(cylinder->height, cylinder->axis)));
        if ((dot_vec(vec_disc, vec_disc) <= cylinder->radius * cylinder->radius) && (closest_inter == -1 || disc < closest_inter))
        {
            closest_inter = disc;
        }
    }
    t = closest_inter;
	if (t > 0)
	{
		res_ambient = ambient_lighting(&rt->scene->amb, cylinder);
		res_colour.red = fmin(255, 255 * res_ambient.red);
		res_colour.green = fmin(255, 255 * res_ambient.green);
		res_colour.blue = fmin(255, 255 * res_ambient.blue);
		spots = rt->scene->lighting.array;
		i = 0;
		while (spots[i])
		{
			hit_point = vec_addition(ray->origin, vec_multiplication(t, ray->dir));
			normal = vec_subtraction(hit_point, cylinder->centre);
			norm_vec(&normal); // only works for the tube
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

void	draw_cylinder(t_rt *rt, t_geometry *geom, int id)
{
	int	x;
	int	y;
	t_ray	ray;
	t_cylinder	transformedcylinder;

	transformedcylinder.centre = base_transform(rt->camtransform, ((t_cylinder *)geom->elem)->centre);
	transformedcylinder.axis = base_transform(rt->camtransform, ((t_cylinder *)geom->elem)->axis);
	transformedcylinder.radius = ((t_cylinder *)geom->elem)->radius;
	transformedcylinder.height = ((t_cylinder *)geom->elem)->height;
	transformedcylinder.colour = ((t_cylinder *)geom->elem)->colour;
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray_launcher(rt, &ray, x, y);
			hit_cylinder(&transformedcylinder, &ray, rt, x, y, id);
			x++;
		}
		y++;
	}
}

