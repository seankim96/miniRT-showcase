/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:05 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:47:51 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../texture.h"

t_color	solid_value(void *solid, double u, double v, t_vector p)
{
	t_solid_texture	*t;

	(void)u;
	(void)v;
	(void)p;
	t = (t_solid_texture *)solid;
	return (t->albedo);
}

void	solid_free(void *solid)
{
	t_solid_texture	*t;

	t = (t_solid_texture *)solid;
	free(t);
}

void	solid_modify_color(void *self, t_bool is_neg)
{
	t_solid_texture	*solid;

	solid = self;
	if (is_neg == true)
		solid->albedo = vector_scalar(solid->albedo, 0.9);
	else
		solid->albedo = vector_scalar(solid->albedo, 1.1);
}

t_texture	*make_texture_solid(t_color color)
{
	t_solid_texture	*solid;

	solid = (t_solid_texture *)ft_calloc(1, sizeof(t_solid_texture));
	solid->albedo = color;
	solid->base.f.free = solid_free;
	solid->base.f.value = solid_value;
	solid->base.f.value_modify = solid_modify_color;
	return ((t_texture *)solid);
}
