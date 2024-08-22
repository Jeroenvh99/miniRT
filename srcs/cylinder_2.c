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

double	hit_cap_1(double disc, double closest_inter, t_ray *ray,
	t_cylinder *cylinder)
{
	t_XYZ	point_disc;
	t_XYZ	vec_disc;

	if (disc >= 0)
	{
		point_disc = vec_addition(ray->origin, vec_multiplication(disc,
					ray->dir));
		vec_disc = vec_subtraction(point_disc, cylinder->centre);
		if ((dot_vec(&vec_disc, &vec_disc) <= cylinder->radius
				* cylinder->radius) && (closest_inter == -1
				|| disc < closest_inter))
		{
			return (disc);
		}
	}
	return (closest_inter);
}

double	hit_cap_2(double disc, double closest_inter, t_ray *ray,
	t_cylinder *cylinder)
{
	t_XYZ	point_disc;
	t_XYZ	vec_disc;

	if (disc >= 0)
	{
		point_disc = vec_addition(ray->origin, vec_multiplication(disc,
					ray->dir));
		vec_disc = vec_subtraction(point_disc, vec_addition(cylinder->centre,
					vec_multiplication(cylinder->height, cylinder->axis)));
		if ((dot_vec(&vec_disc, &vec_disc) <= pow(cylinder->radius, 2))
			&& (closest_inter == -1 || disc < closest_inter))
		{
			return (disc);
		}
	}
	return (closest_inter);
}

double	hit_tube(double inter, double closest_inter, double sol,
	t_cylinder *cylinder)
{
	if ((inter >= 0 && inter <= cylinder->height) && (sol >= 0
			&& (closest_inter == -1 || sol < closest_inter)))
	{
		return (sol);
	}
	return (closest_inter);
}
