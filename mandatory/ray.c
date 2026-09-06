/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:13:52 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:29:45 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "matrix.h"

t_ray	init_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.dir = direction;
	ray.orig = origin;
	ray.tm = 0;
	return (ray);
}

t_vector	ray_at(t_ray self, double t)
{
	return (vector_add(self.orig, vector_scalar(self.dir, t)));
}

t_ray	ray_transform(t_ray r, t_matrix_4x4 matrix)
{
	t_ray	ray;

	ray.orig = matrix_multi_point(r.orig, matrix);
	ray.dir = matrix_multi_vector(r.dir, matrix);
	ray.tm = r.tm;
	return (ray);
}
