/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:10:44 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/16 12:24:04 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H
# include "structs.h"

t_XYZ	vec_addition(t_XYZ vec1, t_XYZ vec2);
t_XYZ	vec_multiplication(double factor, t_XYZ vector);
t_XYZ	vec_subtraction(t_XYZ vec1, t_XYZ vec2);
double	dot_vec(t_XYZ vec1, t_XYZ vec2);
t_XYZ	cross_vec(t_XYZ vec1, t_XYZ vec2);
double	mag_vec(t_XYZ vector);
t_XYZ	norm_vec(t_XYZ vector);
#endif