/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:04:50 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/21 18:20:10 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	double	a;
	double	b;
	double	delta;
	double	sol[2];
	t_XYZ	diff;

	diff = vec_subtraction(ray->origin, sphere->centre);
	a = dot_vec(&ray->dir, &ray->dir);
	b = 2 * dot_vec(&diff, &ray->dir);
	delta = b * b - 4 * a * (dot_vec(&diff, &diff) - sphere->radius
			* sphere->radius);
	if (delta < 0)
		return (-1.0);
	sol[0] = (-b - sqrt(delta)) / (2.0 * a);
	sol[1] = (-b + sqrt(delta)) / (2.0 * a);
	if (sol[0] > 0 && sol[1] > 0)
	{
		return (fmin(sol[0], sol[1]));
	}
	else if (sol[0] > 0 || sol[1] > 0)
		return (fmax(sol[0], sol[1]));
	else
		return (-1.0);
}

uint32_t	pack_colour(t_colour *colour)
{
	int	r;
	int	g;
	int	b;

	r = (int)colour->red;
	g = (int)colour->green;
	b = (int)colour->blue;
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	draw_sphere_2(t_rt *rt, t_colour_3d_object_info *info,
	int coordinate[2], t_sphere *transformedsphere)
{
	double	t;

	ray_launcher(rt, &info->ray, coordinate[0], coordinate[1]);
	t = hit_sphere(transformedsphere, &info->ray);
	if (t > 0)
		colour_3d_object(rt, info, coordinate, t);
}

void	draw_sphere(t_rt *rt, t_geometry *geom, int id)
{
	int						coordinate[2];
	t_colour_3d_object_info	info;
	t_sphere				transformedsphere;

	transformedsphere.centre = base_transform(rt->camtransform,
			&((t_sphere *)geom->elem)->centre);
	transformedsphere.radius = ((t_sphere *)geom->elem)->radius;
	info.colour = &((t_sphere *)geom->elem)->colour;
	info.centre = &transformedsphere.centre;
	info.id = id;
	coordinate[1] = 0;
	while (coordinate[1] < rt->height)
	{
		coordinate[0] = 0;
		while (coordinate[0] < rt->width)
		{
			draw_sphere_2(rt, &info, coordinate, &transformedsphere);
			coordinate[0]++;
		}
		coordinate[1]++;
	}
}
