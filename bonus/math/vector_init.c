/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:38:24 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/04 18:39:13 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raytracing.h"

t_vector	x_vector(void)
{
	return ((t_vector){.x = 1});
}

t_vector	y_vector(void)
{
	return ((t_vector){.y = 1});
}

t_vector	z_vector(void)
{
	return ((t_vector){.z = 1});
}
