/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:13:58 by sean              #+#    #+#             */
/*   Updated: 2025/07/16 13:18:08 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"

void	pad_to_minimums(t_aabb *self)
{
	const double	delta = 0.0001;

	if (interval_size(self->x) < delta)
		self->x = (t_interval){\
			.min = self->x.min - delta / 2, .max = self->x.max + delta / 2};
	if (interval_size(self->y) < delta)
		self->y = (t_interval){\
			.min = self->y.min - delta / 2, .max = self->y.max + delta / 2};
	if (interval_size(self->z) < delta)
		self->z = (t_interval){\
			.min = self->z.min - delta / 2, .max = self->z.max + delta / 2};
}

void	set_ray_interval(double t0, double t1, t_interval *r_t)
{
	if (t0 < t1)
	{
		if (t0 > r_t->min)
			r_t->min = t0;
		if (t1 < r_t->max)
			r_t->max = t1;
	}
	else
	{
		if (t1 > r_t->min)
			r_t->min = t1;
		if (t0 < r_t->max)
			r_t->max = t0;
	}
}

int	longest_axis(t_aabb bbox)
{
	int	x_size;
	int	y_size;
	int	z_size;

	x_size = interval_size(bbox.x);
	y_size = interval_size(bbox.y);
	z_size = interval_size(bbox.z);
	if (x_size > y_size)
	{
		if (x_size > z_size)
			return (0);
		else
			return (2);
	}
	else
	{
		if (y_size > z_size)
			return (1);
		else
			return (2);
	}
}
