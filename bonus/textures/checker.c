/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 23:37:18 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:46:40 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../texture.h"

t_color	checker_value(void *self, double u, double v, t_vector p)
{
	t_checker_texture	*t;
	t_bool				is_even;
	int					check1;
	int					check2;

	t = (t_checker_texture *)self;
	check1 = (int)floor(t->inv_scale * u);
	check2 = (int)floor(t->inv_scale * v);
	is_even = ((check1 + check2) % 2 == 0);
	if (is_even == true)
		return (t->even->f.value(t->even, u, v, p));
	else
		return (t->odd->f.value(t->odd, u, v, p));
}

void	checker_free(void *solid)
{
	t_checker_texture	*t;

	t = (t_checker_texture *)solid;
	if (t->even)
	{
		t->even->reference_count--;
		if (t->even->reference_count == 0)
			t->even->f.free(t->even);
	}
	if (t->odd)
	{
		t->odd->reference_count--;
		if (t->odd->reference_count == 0)
			t->odd->f.free(t->odd);
	}
	free(t);
}

void	checker_modify_color(void *self, t_bool is_neg)
{
	t_checker_texture	*checker;

	checker = self;
	if (checker->even)
		checker->even->f.value_modify(checker->even, is_neg);
	if (checker->odd)
		checker->odd->f.value_modify(checker->odd, is_neg);
}

t_texture	*make_texture_checker(t_color t1, t_color t2, double scale)
{
	t_checker_texture	*checker;

	checker = (t_checker_texture *)ft_calloc(1, sizeof(t_checker_texture));
	checker->inv_scale = 1 / scale;
	checker->even = make_texture_solid(t1);
	checker->odd = make_texture_solid(t2);
	checker->base.f.free = checker_free;
	checker->base.f.value = checker_value;
	checker->base.f.value_modify = checker_modify_color;
	checker->even->reference_count++;
	checker->odd->reference_count++;
	return ((t_texture *)checker);
}
