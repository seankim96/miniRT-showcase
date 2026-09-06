/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:10:14 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:05:55 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector.h"

typedef struct s_matrix_4x4	t_matrix_4x4;

typedef struct s_ray
{
	t_vector	orig;
	t_vector	dir;
	double		tm;
}	t_ray;

t_ray		init_ray(t_vector origin, t_vector direction);
t_vector	ray_at(t_ray self, double t);
t_ray		ray_transform(t_ray r, t_matrix_4x4 matrix);
#endif
