/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:52:43 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:53:17 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_matrix_4x4	matrix_multiply(t_matrix_4x4 a, t_matrix_4x4 b)
{
	t_matrix_4x4	matrix;
	int				i;
	int				j;
	int				k;

	matrix = (t_matrix_4x4){0};
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			while (++k < 4)
			{
				matrix.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}
	return (matrix);
}

t_matrix_4x4	matrix_transpose(t_matrix_4x4 mat)
{
	t_matrix_4x4	result;
	int				i;
	int				j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = mat.m[j][i];
			j++;
		}
		i++;
	}
	return (result);
}
