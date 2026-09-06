/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:11:10 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 16:11:48 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

double	linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return (sqrtf(linear_component));
	return (0);
}

t_color	write_color(t_color color)
{
	double	r;
	double	g;
	double	b;
	t_color	rgb;

	r = linear_to_gamma(color.x);
	g = linear_to_gamma(color.y);
	b = linear_to_gamma(color.z);
	if (r > 1)
		r = 1;
	if (g > 1)
		g = 1;
	if (b > 1)
		b = 1;
	rgb.vector[0] = (int)(r * 255.999);
	rgb.vector[1] = (int)(g * 255.999);
	rgb.vector[2] = (int)(b * 255.999);
	return (rgb);
}
