/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:35:43 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/18 20:31:13 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit_cylinder(t_cylinder cylinder, t_ray ray, double *output)
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

	diff = vec_subtract(ray.origin, cylinder.centre);
	a = dot_prod(ray.dir, ray.dir) - dot_prod(ray.dir, cylinder.axis) * dot_prod(ray.dir, cylinder.axis);
	b = 2 * (dot_prod(ray.dir, diff) - dot_prod(ray.dir, cylinder.axis) * dot_prod(diff, cylinder.axis));
	c = dot_prod(diff, diff) - dot_prod(diff, cylinder.axis) * dot_prod(diff, cylinder.axis) - cylinder.radius * cylinder.radius;
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
		inter1 = dot_prod(ray.dir, cylinder.axis) * sol1 + dot_prod(diff, cylinder.axis);
		inter2 = dot_prod(ray.dir, cylinder.axis) * sol2 + dot_prod(diff, cylinder.axis);
		if ((inter1 >= 0 && inter1 <= cylinder.height) && (sol1 >= 0 && (closest_inter == -1 || sol1 < closest_inter)))
		{
			closest_inter = sol1;
		}
		if ((inter2 >= 0 && inter2 <= cylinder.height) && (sol2 >= 0 && (closest_inter == -1 || sol2 < closest_inter)))
		{
			closest_inter = sol2;
		}
	}
	disc = -dot_prod(diff, cylinder.axis) / dot_prod(ray.dir, cylinder.axis);
	if (disc >= 0)
	{
		point_disc = vec_addition(ray.origin, vec_multiplication(disc, ray.dir));
		vec_disc = vec_subtract(point_disc, cylinder.center);
		if (dot_prod(vec_disc, vec_disc) <= cylinder.radius * cylinder.radius && (closest_inter == -1) || disc < closest_inter)
		{
			closest_inter = disc;
		}
	}
	disc = (cylinder.height - dot_prod(diff, cylinder.axis)) / dot_prod(ray.dir, cylinder.axis);
	if (disc >= 0)
	{
		point_disc = vec_addition(ray.origin, vec_multiplication(disc, ray.dir));
		vec_disc = vec_subtract(point_disc, vec_addition(cylinder.center, vec_multiplication(cylinder.height, cylinder.axis)));
		if (dot_prod(vec_disc, vec_disc) <= cylinder.radius * cylinder.radius && (closest_inter == -1) || disc < closest_inter)
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
}