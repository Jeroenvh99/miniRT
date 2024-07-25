/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:23:54 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/20 16:16:22 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
	{
		write(2, "Please provide a scene to render\n", 33);
		return (1);
	}
	rt.scene = initscene();
	readscene(rt.scene, argv[1]);
	if (checkscene(rt.scene) == 0)
	{
		free_scene(rt.scene, 0);
		return (1);
	}
	build_arrays(rt.scene);
	init_rt(&rt);
	draw_objects(&rt);
	mlx_loop_hook(rt.mlx, set_resize, &rt);
	mlx_loop_hook(rt.mlx, escape_hook, &rt);
	mlx_loop_hook(rt.mlx, resize_render, &rt);
	mlx_loop_hook(rt.mlx, rotate_camera, &rt);
	mlx_key_hook(rt.mlx, reset_resize, &rt);
	mlx_resize_hook(rt.mlx, resize_rt, &rt);
	mlx_loop(rt.mlx);
	exit_rt(&rt);
	return (0);
}
