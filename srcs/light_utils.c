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

t_colour	ambient_lighting(t_ambient *ambient, t_colour *colour)
{
	t_colour	res_ambient;

	res_ambient.red = (ambient->intensity * ambient->colour.red
			+ colour->red);
	res_ambient.green = (ambient->intensity * ambient->colour.green
			+ colour->green);
	res_ambient.blue = (ambient->intensity * ambient->colour.blue
			+ colour->blue);
	return (res_ambient);
}

t_colour	diffuse_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal)
{
	double		diffuse_factor;
	t_colour	res_diffuse;

	diffuse_factor = fmax(dot_vec(*normal, *dir), 0.0);
	res_diffuse.red = (light->brightness * diffuse_factor * light->colour.red);
	res_diffuse.green = (light->brightness * diffuse_factor
			* light->colour.green);
	res_diffuse.blue = (light->brightness * diffuse_factor
			* light->colour.blue);
	return (res_diffuse);
}

t_colour	specular_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal,
		t_XYZ *viewdirection)
{
	t_XYZ		reflection;
	double		spec;
	t_colour	res_spec;

	reflection = vec_subtraction(vec_multiplication(2 * dot_vec(*normal, *dir),
				*normal), *dir);
	spec = pow(fmax(dot_vec(reflection, *viewdirection), 0.0), SHINE);
	res_spec.red = (light->brightness * spec * light->colour.red);
	res_spec.green = (light->brightness * spec * light->colour.green);
	res_spec.blue = (light->brightness * spec * light->colour.blue);
	return (res_spec);
}
