/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:04:04 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:04:05 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include "./math/quaternion.h"

typedef struct s_wrapper		t_wrapper;
typedef struct s_transform_info	t_transform_info;

typedef struct s_matrix_4x4
{
	double	m[4][4];
}	t_matrix_4x4;

t_vector		matrix_multi_point(t_vector p, t_matrix_4x4 matrix);
t_vector		matrix_multi_vector(t_vector p, t_matrix_4x4 matrix);
t_matrix_4x4	matrix_create_uniform(void);
t_matrix_4x4	matrix_scale(t_vector scale);
t_matrix_4x4	matrix_translate(t_vector pos);
t_matrix_4x4	matrix_rotate(t_quaternion rotation);
void			update_matrix_transform(t_transform_info *trans_info);
t_matrix_4x4	matrix_transpose(t_matrix_4x4 mat);
t_matrix_4x4	matrix_create_shear(t_vector xy_xz_yz, t_vector yz_zx_zy);
t_matrix_4x4	matrix_multiply(t_matrix_4x4 a, t_matrix_4x4 b);

#endif
