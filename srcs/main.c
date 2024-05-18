/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:23:54 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/17 19:39:09 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_rt	rt;

	if (argc != 2)
		return (1);
	rt.scene = initscene();
	readscene(rt.scene, argv[1]);
	if (checkscene(rt.scene) == 0)
	{
		free_scene(rt.scene, 0);
		return (1);
	}
	build_arrays(rt.scene);
	init_rt(&rt);
	draw_sphere(&rt);
	mlx_key_hook(rt.mlx, set_resize, &rt);
	mlx_loop(rt.mlx);
	exit_rt(&rt);
	return (0);
}
