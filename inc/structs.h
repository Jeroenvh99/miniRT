/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:24:19 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/16 20:52:09 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_XYZ
{
	double	x;
	double	y;
	double	z;
}	t_XYZ;

/*typedef struct s_color
{
	uint32_t	r;
	uint32_t	b;
	uint32_t	g;
}	t_color;*/

typedef struct s_ray
{
	t_XYZ	origin;
	t_XYZ	dir;
}	t_ray;

typedef struct s_win
{
	int	width;
	int	height;
}	t_win;

typedef struct s_light
{
	t_XYZ	direction;
	uint32_t	color;
	double	intensity;
}	t_light;

typedef struct s_ambient
{
	uint32_t	color;
	double	intensity;
}	t_ambient;

typedef struct s_sp
{
	t_XYZ	center;
	uint32_t	color;
	double	radius;
}	t_sp;

typedef struct s_camera
{
	t_XYZ	origin;
	t_XYZ	norm;
	double	fov;
}	t_camera;

typedef struct s_cylinder
{
	t_XYZ	center;
	t_XYZ	axis;
	double	radius;
	double	height;
	uint32_t	color;
}	t_cylinder;

typedef struct s_data
{
	t_light source;
	t_ambient ambient;
	t_sp	sphere;
	t_camera	camera;
}	t_data;

#endif
