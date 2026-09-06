/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:32:23 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:38:27 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raytracing.h"

t_vector	vector_unit(t_vector vec)
{
	return (vector_scalar(vec, (1.0 / vector_length(vec))));
}

t_bool	vector_near_zero(t_vector v)
{
	const double	s = 1e-4;

	return (fabs(v.x) < s && fabs(v.y) < s && fabs(v.z) < s);
}

t_vector	vector_reflect(t_vector v, t_vector n)
{
	t_vector	reflected;

	reflected = vector_sub(v, vector_scalar(n, 2 * vector_dot(v, n)));
	return (reflected);
}

t_vector	vector_refract(t_vector uv, t_vector n, double etai_over_etat)
{
	double		cos_theta;
	t_vector	r_out_perp;
	t_vector	r_out_parallel;

	cos_theta = fmin(vector_dot(vector_scalar(uv, -1), n), 1.0);
	r_out_perp = vector_scalar((vector_add(uv, \
		vector_scalar(n, cos_theta))), etai_over_etat);
	r_out_parallel = vector_scalar(n, fabs(1 - vector_square(r_out_perp)));
	return (vector_add(r_out_perp, r_out_parallel));
}
