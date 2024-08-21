/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:20:05 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/08/19 15:37:10 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "MLX42.h"
# include "debug.h"
# include "libft.h"
# include "scene.h"
# include <math.h>
# include <float.h>
# define SHINE 80
# define HISTORYSIZE 3

typedef struct s_history
{
	int			index;
	t_geometry	*geom;
}				t_history;

typedef struct s_hit
{
	double		dist;
	uint32_t	colour;
	int			elemid;
}				t_hit;

typedef struct s_colour_3d_object_info
{
	t_ray		ray;
	t_colour	*colour;
	t_XYZ		*centre;
	int			id;
}				t_colour_3d_object_info;

typedef struct s_colour_2d_object_info
{
	t_ray		ray;
	t_colour	*colour;
	t_XYZ		*normal;
	int			id;
}				t_colour_2d_object_info;

typedef struct s_rt
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_history	history[HISTORYSIZE];
	int			width;
	int			height;
	int			totalpixels;
	double		lastresize;
	double		aspectratio;
	double		xrotation;
	double		yrotation;
	double		zrotation;
	t_hit		*pixeldata;
	double		camtransform[3][3];
	t_scene		*scene;
}				t_rt;

typedef void	(*t_drawfunc)(t_rt *, t_geometry *, int);
typedef void	*(*t_copyfunc)(void *);

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
double			dot_vec(t_XYZ *vec1, t_XYZ *vec2);
t_XYZ			cross_vec(t_XYZ *vec1, t_XYZ *vec2);
double			mag_vec(t_XYZ *vector);
void			norm_vec(t_XYZ *vector);
void			default_matrix(t_rt *rt);
void			default_matrix_rotate(t_rt *rt, double xrotation, double yrotation, double zrotation);
t_XYZ			base_transform(double matrix[3][3], t_XYZ *dir);

// resize geometry functions
void			resize_elements(t_rt *rt, int i);
void			changedimension(double *param, char *dimension);
void			changexyz(t_XYZ *xyz, char *type);
void			changecolour(t_colour *colour);
void			copypos(t_XYZ *src, t_XYZ *dst);
void			copycolour(t_colour *src, t_colour *dst);
void			*copysphere(void *sourceelem);
void			*copyplane(void *sourceelem);
void			*copycylinder(void *sourceelem);
t_geometry		*copygeom(t_geometry *source);
void			moveback(t_history *history);

// MLX hooks
void			set_resize(void *rt);
void			reset_resize(mlx_key_data_t keydata, void *param);
void			escape_hook(void *param);
void			resize_rt(int32_t width, int32_t height, void *param);
void			resize_render(void *param);
void			rotate_camera(void *param);

// draw functions
void			draw_objects(t_rt *rt);
void			draw_sphere(t_rt *rt, t_geometry *geometry, int id);
void			draw_plane(t_rt *rt, t_geometry *geom, int id);
void			draw_cylinder(t_rt *rt, t_geometry *geom, int id);
uint32_t		pack_colour(t_colour *colour);
void			ray_launcher(t_rt *rt, t_ray *ray, double x, double y);
void			colour_2d_object(t_rt *rt, t_colour_2d_object_info *info, int coordinate[2], double t);
void			colour_3d_object(t_rt *rt, t_colour_3d_object_info *info, int coordinate[2], double t);

// lighting functions
t_colour		ambient_lighting(t_ambient *ambient, t_colour *colour);
t_colour		diffuse_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal);
t_colour		specular_lighting(t_lighting *light, t_XYZ *dir, t_XYZ *normal,
		t_XYZ *viewdirection);

#endif