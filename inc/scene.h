/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 14:20:28 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/03/20 13:43:45 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
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
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_colour;

typedef struct s_ambient
{
	unsigned char	ratio;
	t_colour		colour;
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
	t_XYZ			pos;
	unsigned char	brightness;
	t_colour		colour;
}					t_lighting;

typedef struct s_sphere
{
	t_XYZ			centre;
	double			diameter;
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
	double			diameter;
	double			radius;
	double			height;
	t_colour		colour;
}					t_cylinder;

typedef struct s_geometry
{
	char			*elemtype;
	union			u_elem
	{
		t_sphere	*sphere;
		t_plane		*plane;
		t_cylinder	*cylinder;
	} elem;
}					t_geometry;

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
void				free_scene(t_scene *scene, int isarr);
int					checkscene(t_scene *scene);

// parsing function
void				readscene(t_scene *scene, char *scenefile);
void				build_arrays(t_scene *scene);

#endif