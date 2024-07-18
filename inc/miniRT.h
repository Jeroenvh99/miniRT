/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:20:05 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/05/21 18:23:47 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "MLX42.h"
# include "debug.h"
# include "libft.h"
# include "scene.h"
# define SHINE 50
# define HISTORYSIZE 3

typedef struct s_history
{
	int			index;
	t_geometry	*geom;
}				t_history;

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_history	history[HISTORYSIZE];
	int			width;
	int			height;
	double		lastresize;
	int			resizerender;
	double		aspectratio;
	double		camtransform[3][3];
	t_scene		*scene;
}				t_rt;

typedef void	(*t_drawfunc)(t_rt *, t_geometry *);

void			init_rt(t_rt *rt);
void			exit_rt(t_rt *rt);

// vector functions
t_XYZ			vector(double x, double y, double z);
double			distance(t_XYZ *p1, t_XYZ *p2);
double			distancetoline(t_XYZ *p, t_XYZ *linepoint, t_XYZ *dir);
int				online(t_XYZ *point, t_ray *line);
int				same_point(t_XYZ *p1, t_XYZ *p2);
t_XYZ			vec_addition(t_XYZ vec1, t_XYZ vec2);
t_XYZ			vec_multiplication(double factor, t_XYZ vector);
t_XYZ			vec_subtraction(t_XYZ vec1, t_XYZ vec2);
double			dot_vec(t_XYZ vec1, t_XYZ vec2);
t_XYZ			cross_vec(t_XYZ vec1, t_XYZ vec2);
double			mag_vec(t_XYZ *vector);
void			norm_vec(t_XYZ *vector);

// resize geometry functions
void			resize_elements(t_rt *rt, int i);
void			changedimension(double *param, char *dimension);
void			changexyz(t_XYZ *xyz, char *type);
void			changecolour(t_colour *colour);

// MLX hooks
void			set_resize(void *rt);
void			reset_resize(mlx_key_data_t keydata, void *param);
void			escape_hook(void *param);
void			resize_rt(int32_t width, int32_t height, void *param);
void			resize_render(void *param);

// draw functions
void			draw_objects(t_rt *rt);
void			draw_sphere(t_rt *rt, t_geometry *geometry);
t_ray			ray_launcher(t_rt *rt, t_ray ray, double x, double y);

#endif