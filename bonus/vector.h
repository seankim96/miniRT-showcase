/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:39:44 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:10:34 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef union u_vector
{
	struct {
		double	x;
		double	y;
		double	z;
	};
	double	vector[3];
}	t_vector;

typedef enum e_bool	t_bool;

t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_scalar(t_vector v1, double scalar);
double		vector_dot(t_vector vec, t_vector v2);
double		vector_square(t_vector vec);
t_vector	vector_cross(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
double		vector_length(t_vector v);
t_vector	vector_unit(t_vector v);
t_vector	vector_mul(t_vector v1, t_vector v2);
t_bool		vector_near_zero(t_vector v);
t_vector	vector_random_unit(void);
t_vector	vector_scalar_div(t_vector vec, double scalar);
t_vector	vector_reflect(t_vector v, t_vector n);
t_vector	vector_refract(t_vector uv, t_vector n, double etai_over_etat);
t_vector	z_vector(void);
t_vector	y_vector(void);
t_vector	x_vector(void);

#endif
