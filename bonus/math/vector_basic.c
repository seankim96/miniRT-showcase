/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:29:39 by sean              #+#    #+#             */
/*   Updated: 2025/07/16 13:18:08 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raytracing.h"

double	vector_dot(t_vector v1, t_vector v2)
{
	double	ans;

	ans = v1.vector[0] * v2.vector[0];
	ans += v1.vector[1] * v2.vector[1];
	ans += v1.vector[2] * v2.vector[2];
	return (ans);
}

t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	ans;

	ans.x = v1.y * v2.z - v1.z * v2.y;
	ans.y = v1.z * v2.x - v1.x * v2.z;
	ans.z = v1.x * v2.y - v1.y * v2.x;
	return (ans);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;
	int			i;

	i = -1;
	while (++i < 3)
		result.vector[i] = v1.vector[i] + v2.vector[i];
	return (result);
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	result;
	int			i;

	i = -1;
	while (++i < 3)
		result.vector[i] = v1.vector[i] - v2.vector[i];
	return (result);
}

t_vector	vector_scalar(t_vector vec, double scalar)
{
	t_vector	result;
	int			i;

	i = -1;
	while (++i < 3)
		result.vector[i] = vec.vector[i] * scalar;
	return (result);
}
