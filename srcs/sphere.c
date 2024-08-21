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

double	hit_sphere(t_sphere *sphere, t_ray *ray)
{
	double	a;
	double	b;
	double	delta;
	double	sol1;
	double	sol2;
	t_XYZ	diff;

	diff = vec_subtraction(ray->origin, sphere->centre);
	a = dot_vec(ray->dir, ray->dir);
	b = 2 * dot_vec(diff, ray->dir);
	delta = b * b - 4 * a * (dot_vec(diff, diff) - sphere->radius
			* sphere->radius);
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
	int			coordinate[2];
	double		t;
	t_ray		ray;
	t_sphere	transformedsphere;

	transformedsphere.centre = base_transform(rt->camtransform,
			&((t_sphere *)geom->elem)->centre);
	transformedsphere.radius = ((t_sphere *)geom->elem)->radius;
	transformedsphere.colour = ((t_sphere *)geom->elem)->colour;
	coordinate[1] = 0;
	while (coordinate[1] < rt->height)
	{
		coordinate[0] = 0;
		while (coordinate[0] < rt->width)
		{
			ray_launcher(rt, &ray, coordinate[0], coordinate[1]);
			t = hit_sphere(&transformedsphere, &ray);
			if (t > 0)
			{
				colour_3d_object(rt, &ray, &transformedsphere.colour, &transformedsphere.centre, coordinate, t, id);
			}
			coordinate[0]++;
		}
		coordinate[1]++;
	}
}
