/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 13:14:38 by jvan-hal      #+#    #+#                 */
/*   Updated: 2024/02/07 18:14:50 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

typedef struct s_scene	t_scene;

void					print_scene(int fd, t_scene *scene);

#endif