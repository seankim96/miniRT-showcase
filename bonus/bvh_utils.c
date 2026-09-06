/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:19:06 by sean              #+#    #+#             */
/*   Updated: 2025/06/27 17:38:39 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_node.h"

t_bool	box_compare(t_hittable *a, t_hittable *b, int axis)
{
	t_interval	a_interval;
	t_interval	b_interval;

	a_interval = a->f.bounding_box(a).vector[axis];
	b_interval = b->f.bounding_box(b).vector[axis];
	if (a_interval.min < b_interval.min)
		return (true);
	else
		return (false);
}

t_bool	x_box_compare(void *a, void *b)
{
	return (box_compare(*((t_hittable **)a), (*(t_hittable **)b), 0));
}

t_bool	y_box_compare(void *a, void *b)
{
	return (box_compare(*((t_hittable **)a), (*(t_hittable **)b), 1));
}

t_bool	z_box_compare(void *a, void *b)
{
	return (box_compare(*((t_hittable **)a), (*(t_hittable **)b), 2));
}
