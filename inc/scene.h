/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:20:28 by jvan-hal          #+#    #+#             */
/*   Updated: 2024/08/21 17:33:25 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# include "libft.h"
# define SCENE_H

enum				e_input_parts
{
	SPACE,
	NUMBERS,
};

typedef struct s_XYZ
{
	double			x;
	double			y;
	double			z;
}					t_XYZ;

typedef struct s_colour
{
	double	red;
	double	green;
	double	blue;
	double	transparency;
}					t_colour;

typedef struct s_ambient
{
	t_colour		colour;
	double			intensity;
}					t_ambient;

typedef struct s_camera
{
	t_XYZ			pos;
	t_XYZ			viewdirection;
	unsigned char	fov;
	float			scale;
}					t_camera;

typedef struct s_lighting
{
	t_XYZ			direction;
	t_colour		colour;
	double			brightness;
}					t_lighting;

typedef struct s_sphere
{
	t_XYZ			centre;
	double			radius;
	t_colour		colour;
}					t_sphere;

typedef struct s_plane
{
	t_XYZ			point;
	t_XYZ			normal;
	t_colour		colour;
}					t_plane;

typedef struct s_cylinder
{
	t_XYZ			centre;
	t_XYZ			axis;
	double			radius;
	double			height;
	t_colour		colour;
}					t_cylinder;

typedef struct s_geometry
{
	int				elemtype;
	void			*elem;
}					t_geometry;

typedef struct s_ray
{
	t_XYZ			origin;
	t_XYZ			dir;
}					t_ray;

typedef struct s_scene
{
	char			*filename;
	t_ambient		amb;
	t_camera		cam;
	union			u_lighting
	{
		t_list		*list;
		t_lighting	**array;
	} lighting;
	union			u_geometry
	{
		t_list		*list;
		t_geometry	**array;
	} geometry;
	int				isresized;
	int				geomsize;
}					t_scene;

t_scene				*initscene(void);
void				free_geom(void *geometry);
void				free_scene(t_scene *scene, int isarr);
int					checkscene(t_scene *scene);
int					spherecollision(t_XYZ *lightpos, t_sphere *sphere);
int					planecollission(t_XYZ *lightpos, t_plane *plane);
int					cylindercollission(t_XYZ *lightpos, t_cylinder *cylinder);
int					checklightcollision(t_scene *scene);

// parsing functions
void				readscene(t_scene *scene, char *scenefile);
void				build_arrays(t_scene *scene);

// printing functions
void				print_colour(int fd, t_colour *colour);
void				print_xyz(int fd, t_XYZ *pos);
void				print_lighting(int fd, t_lighting **lights);
void				print_geometry(int fd, t_geometry **arr);

#endif