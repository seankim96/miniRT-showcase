/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:53:45 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:56:16 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "wrapper.h"

t_vector	matrix_multi_point(t_vector p, t_matrix_4x4 m)
{
	t_vector	result;
	double		w;

	result.x = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2] * p.z + m.m[0][3];
	result.y = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2] * p.z + m.m[1][3];
	result.z = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2] * p.z + m.m[2][3];
	w = m.m[3][0] * p.x + m.m[3][1] * p.y + m.m[3][2] * p.z + m.m[3][3];
	if (w != 1 && w != 0)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return (result);
}

t_vector	matrix_multi_vector(t_vector v, t_matrix_4x4 m)
{
	t_vector	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	return (result);
}

t_matrix_4x4	matrix_create_uniform(void)
{
	t_matrix_4x4	matrix;
	int				i;

	matrix = (t_matrix_4x4){0};
	i = -1;
	while (++i < 4)
		matrix.m[i][i] = 1;
	return (matrix);
}

t_matrix_4x4	matrix_inverse_fast(t_transform_info *info)
{
	t_matrix_4x4	inverse_transform;

	inverse_transform = matrix_multiply(matrix_scale(info->inv_scale), \
	matrix_create_shear(vector_scalar(info->shear_xx_xy_yx, -1), \
	vector_scalar(info->shear_yz_zx_zz, -1)));
	inverse_transform = matrix_multiply(inverse_transform, \
	matrix_rotate(info->r_quat));
	inverse_transform = matrix_multiply(inverse_transform, \
	matrix_translate(vector_scalar(info->pos, -1)));
	return (inverse_transform);
}

void	update_matrix_transform(t_transform_info *trans_info)
{
	const t_matrix_4x4	mat_s = \
	matrix_scale(trans_info->scale);
	const t_matrix_4x4	mat_sh = \
	matrix_create_shear(trans_info->shear_xx_xy_yx, trans_info->shear_yz_zx_zz);
	const t_matrix_4x4	mat_r = \
	matrix_rotate(trans_info->quat);
	const t_matrix_4x4	mat_t = \
	matrix_translate(trans_info->pos);
	t_matrix_4x4		final_transform;

	final_transform = matrix_multiply(mat_t, mat_r);
	final_transform = matrix_multiply(final_transform, mat_sh);
	final_transform = matrix_multiply(final_transform, mat_s);
	trans_info->transform = final_transform;
	trans_info->inv_transform = matrix_inverse_fast(trans_info);
}
