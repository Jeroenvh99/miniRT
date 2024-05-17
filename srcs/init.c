/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 15:40:24 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/03/20 14:03:54 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	set_pixel_colour(uint8_t *pixels, t_colour *colour)
{
	*(pixels++) = (uint8_t)(colour->red);
	*(pixels++) = (uint8_t)(colour->green);
	*(pixels++) = (uint8_t)(colour->blue);
	*(pixels++) = (uint8_t)(0xFF);
}

void	buildcamtransform(t_rt *rt)
{
	t_XYZ	*forward;

	t_XYZ right, up, tmp;
	tmp = vector(0, 1, 0);
	forward = &rt->scene->cam.viewdirection;
	forward = normalize(forward);
	right = cross_prod(&tmp, forward);
	up = cross_prod(forward, &right);
	rt->camtransform[0][0] = right.x;
	rt->camtransform[0][1] = right.y;
	rt->camtransform[0][2] = right.z;
	rt->camtransform[1][0] = up.x;
	rt->camtransform[1][1] = up.y;
	rt->camtransform[1][2] = up.z;
	rt->camtransform[2][0] = forward->x;
	rt->camtransform[2][1] = forward->y;
	rt->camtransform[2][2] = forward->z;
}

// void	draw_objects(t_rt *rt)
// {
// 	int			y;
// 	t_colour	*colour;
// 	int			x;
// 	t_hit		*hit;

// 	y = 0;
// 	colour = &rt->scene->amb.colour;
// 	while (y < rt->height)
// 	{
// 		x = 0;
// 		while (x < rt->width)
// 		{
// 			hit = get_nearest_obj(rt);
// 			// ray.x = (2.0 * (x + 0.5) / (float)rt->width - 1.0)
// 			// 	* rt->aspectratio;
// 			// ray.y = (1.0 - 2.0 * (y + 0.5) / (float)rt->height);
// 			// ray.z = 1.0;
// 			// hit = get_nearest_obj(ray, rt);
// 			set_pixel_colour(rt->image->pixels + ((x + (y * rt->width)) * 4),
// 				colour);
// 			++x;
// 		}
// 		++y;
// 	}
// }

void	write_scene(t_scene *scene)
{
	int	fd;

	fd = open(scene->filename, O_RDONLY | O_WRONLY | O_TRUNC);
	print_scene(fd, scene);
	close(fd);
}

void	init_rt(t_rt *rt)
{
	rt->width = 1280;
	rt->height = 720;
	if (rt->height < rt->width)
		rt->aspectratio = rt->width / rt->height;
	else
		rt->aspectratio = rt->height / rt->width;
	rt->mlx = mlx_init(rt->width, rt->height, "miniRT", false);
	rt->image = mlx_new_image(rt->mlx, rt->width, rt->height);
	mlx_image_to_window(rt->mlx, rt->image, 0, 0);
	// draw_objects(rt);
}

void	exit_rt(t_rt *rt)
{
	char	*res;

	mlx_terminate(rt->mlx);
	if (rt->scene->isresized)
	{
		write(1, "Do you want to save the updated scene[Y/N]:", 43);
		res = get_next_line(0);
		if (*res == 'y' || *res == 'Y')
		{
			write_scene(rt->scene);
		}
		free(res);
	}
	free_scene(rt->scene, 1);
}
