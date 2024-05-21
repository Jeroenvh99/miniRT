/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:20:05 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/20 16:03:19 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "MLX42.h"
# include "debug.h"
# include "libft.h"
# include "scene.h"

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			width;
	int			height;
	float		aspectratio;
	double		camtransform[3][3];
	t_scene		*scene;
}				t_rt;

void			init_rt(t_rt *rt);
void			exit_rt(t_rt *rt);

// vector functions
t_XYZ			vector(double x, double y, double z);
double			distance(t_XYZ *p1, t_XYZ *p2);
double			distancetoline(t_XYZ *p, t_XYZ *linepoint, t_XYZ *dir);
int				same_point(t_XYZ *p1, t_XYZ *p2);
t_XYZ			vec_addition(t_XYZ vec1, t_XYZ vec2);
t_XYZ			vec_multiplication(double factor, t_XYZ vector);
t_XYZ			vec_subtraction(t_XYZ vec1, t_XYZ vec2);
double			dot_vec(t_XYZ vec1, t_XYZ vec2);
t_XYZ			cross_vec(t_XYZ vec1, t_XYZ vec2);
double			mag_vec(t_XYZ vector);
t_XYZ			norm_vec(t_XYZ vector);

// resize geometry functions
void			resize_elements(t_rt *rt);
void			changedimension(double *param, char *dimension);
void			changexyz(t_XYZ *xyz, char *type);
void			changecolour(t_colour *colour);

// MLX hooks
void			set_resize(mlx_key_data_t keydata, void *rt);

// draw functions
void			draw_objects(t_rt *rt);
void			draw_sphere(t_rt *rt, t_sphere sphere);

#endif