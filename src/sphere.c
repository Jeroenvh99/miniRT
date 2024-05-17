/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:04:50 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/17 16:58:24 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "funcs.h"

t_XYZ	ray_constructor(t_XYZ camera, t_XYZ direction, double factor)
{
	t_XYZ	ray;

	ray.x = camera.x + factor * (direction.x);
	ray.y = camera.y + factor * (direction.y);
	ray.z = camera.z + factor * (direction.z);
}

double	sp_interfer(t_sp sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol1;
	double	sol2;
	t_XYZ	diff;

	diff = vec_subtraction(ray.origin, sphere.center);
	a = dot_vec(ray.dir, ray.dir);
	b = - 2 * dot_vec(diff, ray.dir);
	c = dot_vec(diff, diff) - sphere.radius * sphere.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1.0);
	sol1 = (-b - sqrt(delta) / (2.0 * a));
	sol2 = (-b + sqrt(delta) / (2.0 * a));
	if (sol1 > sol2)
		sol1 = sol2;
	if (sol1 < 0)
		return (-1.0);
	return (sol1);
}

uint32_t	light_effect(uint32_t color, double intensity, uint32_t light_color)
{
	int	red;
	int	green;
	int	blue;

	red = (((color >> 16) & 0xFF) * intensity * ((light_color >> 16) & 0xFF) / 255);
	green = (((color >> 8) & 0xFF) * intensity * ((light_color >> 8) & 0xFF) / 255);
	blue = ((color & 0xFF) * intensity * (light_color & 0xFF) / 255);
	return ((red << 16) | (green << 8) | blue);
}

uint32_t	pixel_color(t_sp sphere, t_ray ray, t_ambient ambient, t_light source)
{
	uint32_t	sphere_color;
	uint32_t	result_color;

	if (sp_interfer(sphere, ray) < 0)
	{
		sphere_color = light_effect(sphere.color, source.intensity, source.color);
		result_color = light_effect(sphere_color, ambient.intensity, ambient.color);
	}
	else
		result_color = light_effect(0x000000, ambient.intensity, ambient.color);
	return (result_color);
}

t_XYZ	ray_castor(t_camera camera, int x, int y, int width, int height)
{
	double	aspect_ratio;
	double	scale;
	double	normal_x;
	double	normal_y;
	t_XYZ	dir;
	t_XYZ	up;
	t_XYZ	right;

	aspect_ratio = width / height;
	scale = tan(camera.fov * 0.5 * M_PI / 180.0);
	normal_x = aspect_ratio * scale * ((x + 0.5) / width * 2 - 1);
	normal_y = scale * (1 - (y + 0.5) / height * 2);
	dir = {normal_x, normal_y, -1.0};
	up = {0, 1, 0};
	right = cross_vec(up, camera.norm);
	up = cross_vec(camera.norm, right);
	dir = vec_addition(vec_addition(vec_multiplication(camera.norm, dir.z), vec_multiplication(right, dir.x), vec_multiplication(up, dir.y)));
	return (norm_vec(dir));

}

void	draw_sphere(t_win window, t_data data)
{
	int	x;
	int	y;
	t_ray	ray;
	uint32_t	color;

	y = 0;
	while (y < window.height)
	{
		x = 0;
		while (x < window.width)
		{
			ray.origin = data.camera.origin;
			ray.dir = ray_castor(data.camera, x, y, window.width, window.height);
			color = pixel_color(ray, data.sphere, data.ambient, data.source);
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}