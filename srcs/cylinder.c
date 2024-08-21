/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:43 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/19 15:34:25 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

void	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_rt *rt, int coordinate[2], int id)
{
	t_XYZ		diff;
	t_XYZ		point_disc;
	t_XYZ		vec_disc;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		sol1;
	double		sol2;
	double		holder;
	double		inter1;
	double		inter2;
	double		closest_inter = -1; // Initialize closest_inter to -1
	double		disc;
	double		t;

	diff = vec_subtraction(ray->origin, cylinder->centre);
	a = dot_vec(&ray->dir, &ray->dir) - dot_vec(&ray->dir, &cylinder->axis) * dot_vec(&ray->dir, &cylinder->axis);
	b = 2 * (dot_vec(&ray->dir, &diff) - dot_vec(&ray->dir, &cylinder->axis) * dot_vec(&diff, &cylinder->axis));
	c = dot_vec(&diff, &diff) - dot_vec(&diff, &cylinder->axis) * dot_vec(&diff, &cylinder->axis) - cylinder->radius * cylinder->radius;
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
		inter1 = dot_vec(&ray->dir, &cylinder->axis) * sol1 + dot_vec(&diff, &cylinder->axis);
		inter2 = dot_vec(&ray->dir, &cylinder->axis) * sol2 + dot_vec(&diff, &cylinder->axis);
		if ((inter1 >= 0 && inter1 <= cylinder->height) && (sol1 >= 0 && (closest_inter == -1 || sol1 < closest_inter)))
		{
			closest_inter = sol1;
		}
		if ((inter2 >= 0 && inter2 <= cylinder->height) && (sol2 >= 0 && (closest_inter == -1 || sol2 < closest_inter)))
		{
			closest_inter = sol2;
		}
	}
	disc = -dot_vec(&diff, &cylinder->axis) / dot_vec(&ray->dir, &cylinder->axis);
	if (disc >= 0)
	{
		point_disc = vec_addition(ray->origin, vec_multiplication(disc, ray->dir));
		vec_disc = vec_subtraction(point_disc, cylinder->centre);
		if ((dot_vec(&vec_disc, &vec_disc) <= cylinder->radius * cylinder->radius) && (closest_inter == -1 || disc < closest_inter))
		{
			closest_inter = disc;
		}
	}
	disc = (cylinder->height - dot_vec(&diff, &cylinder->axis)) / dot_vec(&ray->dir, &cylinder->axis);
	if (disc >= 0)
	{
		point_disc = vec_addition(ray->origin, vec_multiplication(disc, ray->dir));
		vec_disc = vec_subtraction(point_disc, vec_addition(cylinder->centre, vec_multiplication(cylinder->height, cylinder->axis)));
		if ((dot_vec(&vec_disc, &vec_disc) <= cylinder->radius * cylinder->radius) && (closest_inter == -1 || disc < closest_inter))
		{
			closest_inter = disc;
		}
	}
	t = closest_inter;
	if (t > 0)
	{
		colour_3d_object(rt, ray, &cylinder->colour, &cylinder->centre, coordinate, t, id);
	}
}

void	draw_cylinder(t_rt *rt, t_geometry *geom, int id)
{
	int			coordinate[2];
	t_ray		ray;
	t_cylinder	transformedcylinder;

	transformedcylinder.centre = base_transform(rt->camtransform, &((t_cylinder *)geom->elem)->centre);
	transformedcylinder.axis = base_transform(rt->camtransform, &((t_cylinder *)geom->elem)->axis);
	transformedcylinder.radius = ((t_cylinder *)geom->elem)->radius;
	transformedcylinder.height = ((t_cylinder *)geom->elem)->height;
	transformedcylinder.colour = ((t_cylinder *)geom->elem)->colour;
	coordinate[1] = 0;
	while (coordinate[1] < rt->height)
	{
		coordinate[0] = 0;
		while (coordinate[0] < rt->width)
		{
			ray_launcher(rt, &ray, coordinate[0], coordinate[1]);
			hit_cylinder(&transformedcylinder, &ray, rt, coordinate, id);
			coordinate[0]++;
		}
		coordinate[1]++;
	}
}
