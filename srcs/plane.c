/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjeddi <sjeddi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:32:04 by sjeddi            #+#    #+#             */
/*   Updated: 2024/05/20 19:07:22 by sjeddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

vec3 calculate_ray_direction(camera cam, int x, int y, int width, int height) {
    double aspect_ratio = (double)width / (double)height;
    double scale = tan(cam.fov * 0.5 * M_PI / 180.0);

    double px = (x + 0.5) / width * 2 - 1;   // Conversion en coordonnées normalisées [-1, 1]
    double py = (y + 0.5) / height * 2 - 1;  // Conversion en coordonnées normalisées [-1, 1]
    px *= aspect_ratio * scale;
    py *= scale;

    // Vecteur de direction local dans l'espace de la caméra
    vec3 dir = {px, py, 1.0};

    // Détermination du système d'axes basé sur la direction de la caméra
    vec3 up = {0, 1, 0};  // Choix arbitraire pour simplifier, à ajuster selon la configuration
    vec3 right = vec_cross(up, cam.direction);
    up = vec_cross(cam.direction, right);

    // Transformation du vecteur de direction en coordonnées mondiales
    dir = vec_add(vec_add(vec_scale(cam.direction, dir.z),
                          vec_scale(right, dir.x)),
                          vec_scale(up, dir.y));

    return unit_vector(dir);
}