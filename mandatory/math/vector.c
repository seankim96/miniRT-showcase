/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:25:33 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/16 13:18:08 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raytracing.h"

t_vector	vector_mul(t_vector v1, t_vector v2)
{
	t_vector	ans;

	ans.x = v1.x * v2.x;
	ans.y = v1.y * v2.y;
	ans.z = v1.z * v2.z;
	return (ans);
}

t_vector	vector_scalar_div(t_vector vec, double scalar)
{
	t_vector	result;
	int			i;

	i = -1;
	while (++i < 3)
		result.vector[i] = vec.vector[i] / scalar;
	return (result);
}

double	vector_square(t_vector vec)
{
	double	len;

	len = vector_dot(vec, vec);
	return (len);
}

double	vector_length(t_vector vec)
{
	double	len;

	len = sqrt(vector_square(vec));
	return (len);
}
