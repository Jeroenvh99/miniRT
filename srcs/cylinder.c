/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:43 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/21 19:36:30 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	solve_abc(double abc[3], t_ray *ray, t_cylinder *cylinder, t_XYZ *diff)
{
	double	sol1;
	double	sol2;
	double	delta;
	double	closest_inter;

	closest_inter = -1;
	delta = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (delta >= 0)
	{
		sol1 = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
		sol2 = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
		if (sol1 > sol2)
		{
			delta = sol1;
			sol1 = sol2;
			sol2 = delta;
		}
		closest_inter = hit_tube(dot_vec(&ray->dir, &cylinder->axis) * sol1
				+ dot_vec(diff, &cylinder->axis), closest_inter, sol1,
				cylinder);
		closest_inter = hit_tube(dot_vec(&ray->dir, &cylinder->axis) * sol2
				+ dot_vec(diff, &cylinder->axis), closest_inter, sol2,
				cylinder);
	}
	return (closest_inter);
}

double	hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_XYZ		diff;
	double		abc[3];
	double		closest_inter;

	closest_inter = -1;
	diff = vec_subtraction(ray->origin, cylinder->centre);
	abc[0] = dot_vec(&ray->dir, &ray->dir) - dot_vec(&ray->dir,
			&cylinder->axis) * dot_vec(&ray->dir, &cylinder->axis);
	abc[1] = 2 * (dot_vec(&ray->dir, &diff) - dot_vec(&ray->dir,
				&cylinder->axis) * dot_vec(&diff, &cylinder->axis));
	abc[2] = dot_vec(&diff, &diff) - dot_vec(&diff, &cylinder->axis)
		* dot_vec(&diff, &cylinder->axis) - pow(cylinder->radius, 2);
	closest_inter = solve_abc(abc, ray, cylinder, &diff);
	closest_inter = hit_cap_1(-dot_vec(&diff, &cylinder->axis)
			/ dot_vec(&ray->dir, &cylinder->axis), closest_inter, ray,
			cylinder);
	closest_inter = hit_cap_2((cylinder->height - dot_vec(&diff,
					&cylinder->axis)) / dot_vec(&ray->dir, &cylinder->axis),
			closest_inter, ray, cylinder);
	return (closest_inter);
}

void	draw_cylinder_2(t_rt *rt, t_colour_3d_object_info *info,
	int coordinate[2], t_cylinder *transformedcylinder)
{
	double	t;

	ray_launcher(rt, &info->ray, coordinate[0], coordinate[1]);
	t = hit_cylinder(transformedcylinder, &info->ray);
	if (t > 0)
		colour_3d_object(rt, info, coordinate, t);
}

void	draw_cylinder(t_rt *rt, t_geometry *geom, int id)
{
	int						coordinate[2];
	t_cylinder				transformedcylinder;
	t_colour_3d_object_info	info;

	transformedcylinder.centre = base_transform(rt->camtransform,
			&((t_cylinder *)geom->elem)->centre);
	transformedcylinder.axis = base_transform(rt->camtransform,
			&((t_cylinder *)geom->elem)->axis);
	transformedcylinder.radius = ((t_cylinder *)geom->elem)->radius;
	transformedcylinder.height = ((t_cylinder *)geom->elem)->height;
	info.colour = &((t_cylinder *)geom->elem)->colour;
	info.centre = &transformedcylinder.centre;
	info.id = id;
	coordinate[1] = 0;
	while (coordinate[1] < rt->height)
	{
		coordinate[0] = 0;
		while (coordinate[0] < rt->width)
		{
			draw_cylinder_2(rt, &info, coordinate, &transformedcylinder);
			coordinate[0]++;
		}
		coordinate[1]++;
	}
}
