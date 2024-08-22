/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 13:28:03 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/01/17 11:28:10 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "scene.h"
# define N_ELEMENTS 6

// typedef struct s_scene	t_scene;
// typedef struct s_colour	t_colour;
// typedef struct s_XYZ	t_XYZ;

typedef int				(*t_parsef)(t_scene *, char *line);

int						checkfilename(char *file);
int						isint(char *str);
int						isdouble(char *str);
int						is_colour(char *str);
int						is_xyz(char *str);
int						comment(char *str);
char					*skipspace(char *in);
void					tabtospace(char *str);
int						splitsize(char **split);
void					free_split(char **arr);
void					parse_colour(char *in, t_colour *color);
void					parse_xyz(char *in, t_XYZ *pos);
int						checkambient(char **parts);
int						checkcamera(char **parts);
int						checklight(char **parts);
int						checksphere(char **parts);
int						checkplane(char **parts);
int						checkcylinder(char **parts);
int						parsesphere(t_scene *scene, char *line);
int						parseplane(t_scene *scene, char *line);
int						parsecylinder(t_scene *scene, char *line);
int						parse_cylinder_2(char **parts);
#endif