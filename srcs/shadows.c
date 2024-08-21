/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:58:35 by sjeddi            #+#    #+#             */
/*   Updated: 2024/08/21 18:24:09 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_object(t_geometry *geom, t_ray *ray, t_rt *rt, int x, int y, int id)
{
	if (geom->elemtype == 1)
		return (hit_sphere((t_sphere*)geom->elem, ray));
	else if (geom->elemtype == 2)
		return (hit_plane((t_plane*)geom->elem, ray, rt, x, y, id));
	else if (geom->elemtype == 3)
		return (hit_cylinder((t_cylinder*)geom->elem, ray, rt, x, y, id));
	else
		return (-1.0);

}
int	shadow_checker(t_ray *ray, t_rt *rt, int x, int y, int id)
{
	t_closest_geom	res;
	int				i;
	t_geometry		*geom;
	double			t;

	res.close_geometry = NULL;
	res.closest_t = 1.0;
	i = 0;
	while (i < rt->scene->geomsize)
	{
		geom = rt->scene->geometry.array[i];
		t = hit_object(geom, ray, rt, x, y, id);
		if (t >= 1e-10 && t <= 1 && t < res.closest_t)
		{
			res.closest_t = t;
			res.close_geometry = geom;
		}
		i++;
	}
	if (res.close_geometry != NULL)
		return (1);
	else
		return (0);

}