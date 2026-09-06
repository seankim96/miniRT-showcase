/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:32:49 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/07/21 13:42:25 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "./math/interval.h"
#include "vector.h"

int	is_between_01(double value)
{
	return (0.0 <= value && value <= 1.0);
}

int	is_fov_in_range(double fov)
{
	return (0.0 <= fov && fov <= 180.0);
}

int	is_rgb_in_range(t_color color)
{
	t_interval	range;

	range = (t_interval){0, 255};
	return (contains(range, color.x)
		&& contains(range, color.y)
		&& contains(range, color.z));
}

int	is_normal_vec(t_vector vec)
{
	return (surrounds((t_interval){0.97, 1.03}, vector_length(vec)));
}

int	is_inf_vec(t_vector vec)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (isnan(vec.vector[i]) || isinf(vec.vector[i]))
			return (1);
		i++;
	}
	return (0);
}
