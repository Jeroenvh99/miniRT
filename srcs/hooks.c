/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 09:57:37 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/02/09 14:31:27 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_resize(mlx_key_data_t keydata, void *rt)
{
	t_rt	*local_rt;

	local_rt = (t_rt *)rt;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		resize_elements(local_rt);
		draw_objects(rt);
	}
}
