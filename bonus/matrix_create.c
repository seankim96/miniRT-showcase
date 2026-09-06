/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:53:48 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:56:23 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix_4x4	matrix_scale(t_vector scale)
{
	t_matrix_4x4	mat;

	mat = matrix_create_uniform();
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	return (mat);
}

t_matrix_4x4	matrix_translate(t_vector pos)
{
	t_matrix_4x4	mat;

	mat = matrix_create_uniform();
	mat.m[0][3] = pos.x;
	mat.m[1][3] = pos.y;
	mat.m[2][3] = pos.z;
	return (mat);
}

t_matrix_4x4	matrix_rotate(t_quaternion q)
{
	t_matrix_4x4	mat;

	mat = matrix_create_uniform();
	mat.m[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
	mat.m[0][1] = 2 * (q.x * q.y - q.z * q.w);
	mat.m[0][2] = 2 * (q.x * q.z + q.y * q.w);
	mat.m[1][0] = 2 * (q.x * q.y + q.z * q.w);
	mat.m[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
	mat.m[1][2] = 2 * (q.y * q.z - q.x * q.w);
	mat.m[2][0] = 2 * (q.x * q.z - q.y * q.w);
	mat.m[2][1] = 2 * (q.y * q.z + q.x * q.w);
	mat.m[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);
	return (mat);
}

t_matrix_4x4	matrix_create_shear(t_vector xy_xz_yz, t_vector yz_zx_zy)
{
	t_matrix_4x4	matrix;

	matrix = matrix_create_uniform();
	matrix.m[0][2] = xy_xz_yz.vector[0];
	matrix.m[0][3] = xy_xz_yz.vector[1];
	matrix.m[1][0] = xy_xz_yz.vector[2];
	matrix.m[1][2] = yz_zx_zy.vector[0];
	matrix.m[2][0] = yz_zx_zy.vector[1];
	matrix.m[2][1] = yz_zx_zy.vector[2];
	return (matrix);
}
