/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:52:02 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:37:51 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interval.h"
#include "../raytracing.h"

t_bool	surrounds(t_interval self, double n)
{
	if (self.min < n && n < self.max)
		return (true);
	return (false);
}

t_bool	contains(t_interval self, double n)
{
	if (self.min <= n && n <= self.max)
		return (true);
	return (false);
}

t_interval	interval_with_num(double min, double max)
{
	t_interval	interval;

	interval.min = min;
	interval.max = max;
	return (interval);
}

t_interval	interval_with_interval(t_interval a, t_interval b)
{
	t_interval	interval;

	if (a.min <= b.min)
		interval.min = a.min;
	else
		interval.min = b.min;
	if (a.max >= b.max)
		interval.max = a.max;
	else
		interval.max = b.max;
	return (interval);
}

double	interval_size(t_interval interval)
{
	double	num;

	num = interval.max - interval.min;
	return (num);
}
