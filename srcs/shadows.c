/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:58:35 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/21 19:51:21 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_object(t_geometry *geom, t_ray *ray)
{
	if (geom->elemtype == 1)
		return (hit_sphere((t_sphere *)geom->elem, ray));
	else if (geom->elemtype == 2)
		return (hit_plane((t_plane *)geom->elem, ray));
	else if (geom->elemtype == 3)
		return (hit_cylinder((t_cylinder *)geom->elem, ray));
	else
		return (-1.0);
}

int	shadow_checker(t_ray *ray, t_rt *rt)
{
	int				i;
	t_geometry		*geom;
	double			closest_t;
	double			t;
	int				ret;

	closest_t = 1.0;
	ret = 0;
	i = 0;
	while (i < rt->scene->geomsize)
	{
		geom = rt->scene->geometry.array[i];
		t = hit_object(geom, ray);
		if (t >= 1e-10 && t <= 1 && t < closest_t)
		{
			closest_t = t;
			ret = 1;
		}
		i++;
	}
	return (ret);
}
