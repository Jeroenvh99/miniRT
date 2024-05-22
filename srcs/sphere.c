/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:04:50 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/21 18:21:43 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <stdio.h>

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
	double	delta;
	double	sol1;
	double	sol2;
	t_XYZ	diff;

	diff = vec_subtraction(ray.origin, sphere.centre);
	a = dot_vec(ray.dir, ray.dir);
	b = 2 * dot_vec(diff, ray.dir);
	delta = b * b - 4 * a * (dot_vec(diff, diff) - sphere.radius * sphere.radius);
	if (delta < 0)
		return (-1.0);
	sol1 = (-b - sqrt(delta)) / (2.0 * a);
	sol2 = (-b + sqrt(delta))/ (2.0 * a);
	if (sol1 > 0 && sol2 > 0)
	{
		return (fmin(sol1, sol2));
	}
	else if (sol1 > 0)
		return (sol1);
	else if (sol2 > 0)
		return (sol2);
	else
		return (-1.0);
}

/*t_colour	pixel_colour(t_sphere sphere, t_ray ray)
{
	t_colour	result_colour;

	if (hit_sphere(sphere, ray) > 0)
	{
		//sphere_colour = light_effect(sphere.colour, source.brightness);
		result_colour = sphere.colour;
	}
	else
	{
		result_colour.red = 0;
		result_colour.green = 0;
		result_colour.blue = 0;
	}
	return (result_colour);
}*/

/*static void	print_XYZ(int fd, t_XYZ *pos)
{
	dprintf(fd, "%f,%f,%f", pos->x, pos->y, pos->z);
}*/

/*t_XYZ	ray_castor(t_camera camera, int x, int y, int width, int height)
{
	double	aspect_ratio;
	double	scale;
	double	normal_x;
	double	normal_y;
	t_XYZ	dir;
	t_XYZ	up;
	t_XYZ	right;

	aspect_ratio = (double)width / (double)height;
	scale = tan(camera.fov * 0.5 * M_PI / 180.0);
	printf("%f\n", scale);
	normal_x = aspect_ratio * scale * (((x + 0.5) / width) * 2 - 1);
	normal_y = scale * (1-(((y + 0.5) / height) * 2));
	dir.x = normal_x;
	dir.y = normal_y;
	dir.z = 1.0;
	up.x = 0;
	up.y = 1;
	up.z = 0;
	right = cross_vec(up, camera.viewdirection);
	up = cross_vec(camera.viewdirection, right);
	//printf("%f\n", );
	print_XYZ(1, &up);
	//print_XYZ(1, &right);
	dir = vec_addition(vec_addition(vec_multiplication(dir.z, camera.viewdirection), vec_multiplication(dir.x, right)), vec_multiplication(dir.y, up));
	//print_XYZ(1, &dir);
	return (norm_vec(dir));

}*/

/*t_XYZ ray_castor(t_camera camera, int x, int y, int width, int height)
{
	t_XYZ	forward;
	t_XYZ	right;
	t_XYZ	up;
	t_XYZ	dir;
	double aspect_ratio = (double)width/(double)height;
	double scale = tan((camera.fov * M_PI * 180) / 2.0);
	double imageX = (2 * (x + 0.5) / (double)width - 1) * aspect_ratio * scale;
	double imageY = (1 - 2 * (y + 0.5) / (double)height) * scale;
	forward.x = -camera.viewdirection.x;
	forward.y = -camera.viewdirection.y;
	forward.z = -camera.viewdirection.z;
	right.x = forward.y;
	right.y = -forward.x;
	right.z = 0;
	up.x = -forward.y * right.z + forward.z * right.y;
	up.y = forward.x * right.z - forward.z * right.x;
	up.z = -forward.x * right.y + forward.y * right.x;
	right = norm_vec(right);
	up = norm_vec(up);
	dir.x = forward.x + imageX * right.x + imageY * up.x;
	dir.y = forward.y + imageX * right.y + imageY * up.y;
	dir.z = forward.z + imageX * right.z + imageY * up.z;
	dir = norm_vec(dir);
	print_XYZ(1, &dir);
	return (dir);
}*/

/*uint32_t pixel_colour(t_sphere sphere, t_ray ray, t_ambient ambient, t_lighting light) {
    t_colour result_colour = {0, 0, 0};
    double t = hit_sphere(sphere, ray);
    if (t >= 0) {
        t_XYZ intersection = vec_addition(ray.origin, vec_multiplication(t, ray.dir));
        t_XYZ normal = norm_vec(vec_subtraction(intersection, sphere.centre));
        t_XYZ light_dir = norm_vec(vec_subtraction(light.position, intersection));
        t_XYZ view_dir = norm_vec(vec_subtraction(ray.origin, intersection));
        t_XYZ reflect_dir = vec_subtraction(vec_multiplication(2.0 * dot_vec(normal, light_dir), normal), light_dir);

        // Ambient component
        double ambient_component = ambient.intensity;
        t_colour ambient_color = {
            (uint8_t)(sphere.colour.red * ambient_component * (ambient.colour.red / 255.0)),
            (uint8_t)(sphere.colour.green * ambient_component * (ambient.colour.green / 255.0)),
            (uint8_t)(sphere.colour.blue * ambient_component * (ambient.colour.blue / 255.0))
        };

        // Diffuse component
        double diffuse = max(0.0, dot_vec(normal, light_dir)) * light.brightness;
        t_colour diffuse_color = {
            (uint8_t)(sphere.colour.red * diffuse * (light.colour.red / 255.0)),
            (uint8_t)(sphere.colour.green * diffuse * (light.colour.green / 255.0)),
            (uint8_t)(sphere.colour.blue * diffuse * (light.colour.blue / 255.0))
        };

        // Specular component
        double shininess = 32.0;  // Adjust shininess factor as needed
        double specular = pow(max(0.0, dot_vec(view_dir, reflect_dir)), shininess) * light.brightness;
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
*/
// Include other required functions and definitions here*/

t_colour	ambient_lighting(t_ambient ambient, t_sphere sphere)
{
	t_colour	res_ambient;

	res_ambient.red = (unsigned char)(ambient.intensity * ambient.colour.red * sphere.colour.red / 255);
	res_ambient.green = (unsigned char)(ambient.intensity * ambient.colour.green * sphere.colour.green / 255);
	res_ambient.green = (unsigned char)(ambient.intensity * ambient.colour.blue * sphere.colour.blue / 255);
	return (res_ambient);
}

t_colour	diffuse_lighting(t_lighting light, t_XYZ dir, t_XYZ normal, t_sphere sphere)
{
	double	diffuse_factor;
	t_colour	res_diffuse;

	diffuse_factor = fmax(dot_vec(normal, dir), 0.0);
	res_diffuse.red = (unsigned char)(light.brightness * diffuse_factor * light.colour.red * sphere.colour.red / 255);
	res_diffuse.green = (unsigned char)(light.brightness * diffuse_factor * light.colour.green * sphere.colour.green / 255);
	res_diffuse.blue = (unsigned char)(light.brightness * diffuse_factor * light.colour.blue * sphere.colour.blue / 255);
	return (res_diffuse);
}

t_colour	specular_lighting(t_lighting light, t_XYZ dir, t_XYZ normal, t_XYZ viewdirection, double shininess)
{
	t_XYZ reflection;
	double spec;
	t_colour	res_spec;

	reflection = vec_subtraction(vec_multiplication(2 * dot_vec(normal, dir), normal), dir);
	spec = pow(fmax(dot_vec(reflection, viewdirection), 0.0), shininess);
	res_spec.red = (unsigned char)(light.brightness * spec * light.colour.red);
	res_spec.green = (unsigned char)(light.brightness * spec * light.colour.green);
	res_spec.blue = (unsigned char)(light.brightness * spec * light.colour.blue);
	return (res_spec);
}

t_colour	pixel_colour(t_sphere sphere, t_ray ray, t_ambient ambient, t_lighting light, double shininess)
{
	t_colour	res_colour;
	double t;
	t = hit_sphere(sphere, ray);
	if (t < 0)
		return ((t_colour){0, 0, 0, 0});
	else
	{
		t_XYZ hit_point = vec_addition(ray.origin, vec_multiplication(t, ray.dir));
		t_XYZ	normal = norm_vec(vec_subtraction(hit_point, sphere.centre));
		t_XYZ	light_dir = norm_vec(vec_subtraction(light.direction, hit_point));
		t_XYZ	viewdirection = norm_vec(vec_multiplication(-1, ray.dir));
		t_colour	res_ambient = ambient_lighting(ambient, sphere);
		t_colour	res_diffuse = diffuse_lighting(light, light_dir, normal, sphere);
		t_colour	res_spec = specular_lighting(light, light_dir, normal, viewdirection, shininess);
		res_colour.red = (unsigned char) fmin(255, res_ambient.red + res_diffuse.red + res_spec.red);
		res_colour.green = (unsigned char) fmin(255, res_ambient.green + res_diffuse.green + res_spec.green);
		res_colour.blue = (unsigned char) fmin(255, res_ambient.blue + res_diffuse.blue + res_spec.blue);
		res_colour.transparency = 255;
		return (res_colour);
	}
}

uint32_t pack_colour(t_colour colour)
{
	return (colour.red << 24 | colour.green << 16 | colour.blue << 8 | colour.transparency);
}
void	draw_sphere(t_rt *rt, t_sphere sphere)
{
	double	x;
	double	y;
	t_ray	ray;
	t_colour	tempcolour;
	t_colour	colour;

	//default_matrix(rt);
	y = 0;
	while (y < rt->height)
	{
		x = 0;
		while (x < rt->width)
		{
			ray = ray_launcher(rt, ray, x, y);
			t_lighting **spots;
			spots = rt->scene->lighting.array;
			colour.red = colour.green = colour.blue = colour.transparency = 0;
			int i = 0;
			while (spots[i])
			{
				tempcolour = pixel_colour(sphere, ray, rt->scene->amb, *(rt->scene->lighting.array[i]), SHINE);
				colour.red += tempcolour.red;
				if (colour.red > 255)
					colour.red = 255;
				colour.green += tempcolour.green;
				if (colour.green > 255)
					colour.green = 255;
				colour.blue += tempcolour.blue;
				if (colour.blue > 255)
					colour.blue = 255;
				colour.transparency += tempcolour.transparency;
				if (colour.transparency > 255)
					colour.transparency = 255;
				++i;
			}
			if (colour.transparency > 0)
			{
				mlx_put_pixel(rt->image, x, y, pack_colour(colour));
			}
			x++;
		}
		y++;
	}
}

