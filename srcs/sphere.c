/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:04:50 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/20 16:02:49 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/*t_XYZ	ray_constructor(t_XYZ camera, t_XYZ direction, double factor)
{
	t_XYZ	ray;

	ray.x = camera.x + factor * (direction.x);
	ray.y = camera.y + factor * (direction.y);
	ray.z = camera.z + factor * (direction.z);
}*/

double	hit_sphere(t_sphere sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	sol1;
	double	sol2;
	t_XYZ	diff;

	diff = vec_subtraction(ray.origin, sphere.centre);
	a = dot_vec(ray.dir, ray.dir);
	b = - 2 * dot_vec(diff, ray.dir);
	c = dot_vec(diff, diff) - sphere.radius * sphere.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (-1.0);
	sol1 = (-b - sqrt(delta) / (2.0 * a));
	sol2 = (-b + sqrt(delta) / (2.0 * a));
	if (sol1 > 0 && sol2 > 0)
	{
		if (sol1 > sol2)
			sol1 = sol2;
		return (sol1);
	}
	else if (sol1 > 0)
		return (sol1);
	else if (sol2 > 0)
		return (sol2);
	else
		return (-1.0);
}

t_colour	light_effect(t_colour colour, double intensity)
{
	colour.red *= intensity;
	colour.green *= intensity;
	colour.blue *= intensity;
	return (colour);
}

t_colour	pixel_colour(t_sphere sphere, t_ray ray, t_ambient ambient)
{
	//t_colour	sphere_colour;
	t_colour	result_colour;

	if (hit_sphere(sphere, ray) < 0)
	{
		//sphere_colour = light_effect(sphere.colour, source.brightness);
		result_colour = light_effect(sphere.colour, ambient.intensity);
	}
	else
	{
		result_colour.red = 0;
		result_colour.green = 0;
		result_colour.blue = 0;
	}
	return (result_colour);
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
	dir.x = normal_x;
	dir.y = normal_y;
	dir.z = -1.0;
	up.x = 0;
	up.y = 1;
	up.z = 0;
	right = cross_vec(up, camera.viewdirection);
	up = cross_vec(camera.viewdirection, right);
	dir = vec_addition(vec_addition(vec_multiplication(dir.z, camera.viewdirection), vec_multiplication(dir.x, right)), vec_multiplication(dir.y, up));
	return (norm_vec(dir));

}

uint32_t pack_colour(t_colour colour)
{
	return (colour.red << 24 | colour.green << 16 | colour.blue << 8 | 0xff);
}

void	draw_sphere(t_rt *rt, t_sphere sphere)
{
	int	x;
	int	y;
	t_ray	ray;
	t_colour	colour;

	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray.origin = rt->scene->cam.pos;
			ray.dir = ray_castor(rt->scene->cam, x, y, rt->width, rt->height);
			colour = pixel_colour(sphere, ray, rt->scene->amb);
			mlx_put_pixel(rt->image, x, y, pack_colour(colour));
			x++;
		}
		y++;
	}
}

/*#include <math.h>
#include <stdint.h>

// Define your existing structures and vector operations here

uint32_t pixel_colour(t_sphere sphere, t_ray ray, t_ambient ambient, t_light light) {
    t_colour result_colour = {0, 0, 0};
    double t = hit_sphere(sphere, ray);
    if (t >= 0) {
        t_XYZ intersection = vec_addition(ray.origin, vec_multiplication(t, ray.dir));
        t_XYZ normal = norm_vec(vec_subtraction(intersection, sphere.centre));
        t_XYZ light_dir = norm_vec(vec_subtraction(light.position, intersection));
        t_XYZ view_dir = norm_vec(vec_subtraction(ray.origin, intersection));
        t_XYZ reflect_dir = vec_subtraction(vec_multiplication(2.0 * dot_vec(normal, light_dir), normal), light_dir);

        // Ambient component
        double ambient_component = ambient.ratio;
        t_colour ambient_color = {
            (uint8_t)(sphere.colour.red * ambient_component * (ambient.colour.red / 255.0)),
            (uint8_t)(sphere.colour.green * ambient_component * (ambient.colour.green / 255.0)),
            (uint8_t)(sphere.colour.blue * ambient_component * (ambient.colour.blue / 255.0))
        };

        // Diffuse component
        double diffuse = max(0.0, dot_vec(normal, light_dir)) * light.intensity;
        t_colour diffuse_color = {
            (uint8_t)(sphere.colour.red * diffuse * (light.colour.red / 255.0)),
            (uint8_t)(sphere.colour.green * diffuse * (light.colour.green / 255.0)),
            (uint8_t)(sphere.colour.blue * diffuse * (light.colour.blue / 255.0))
        };

        // Specular component
        double shininess = 32.0;  // Adjust shininess factor as needed
        double specular = pow(max(0.0, dot_vec(view_dir, reflect_dir)), shininess) * light.intensity;
        t_colour specular_color = {
            (uint8_t)(255 * specular * (light.colour.red / 255.0)),
            (uint8_t)(255 * specular * (light.colour.green / 255.0)),
            (uint8_t)(255 * specular * (light.colour.blue / 255.0))
        };

        // Combine components and clamp values to [0, 255]
        result_colour.red = min(255, ambient_color.red + diffuse_color.red + specular_color.red);
        result_colour.green = min(255, ambient_color.green + diffuse_color.green + specular_color.green);
        result_colour.blue = min(255, ambient_color.blue + diffuse_color.blue + specular_color.blue);
    }

    // Pack the color components into a single uint32_t
    return ((uint32_t)result_colour.red << 16) | ((uint32_t)result_colour.green << 8) | (uint32_t)result_colour.blue;
}

// Include other required functions and definitions here*/