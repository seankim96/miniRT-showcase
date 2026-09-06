/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:00:53 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/16 13:18:08 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "aabb.h"
#include "ray.h"

t_aabb	make_bbox(void)
{
	t_aabb	bbox;

	bbox.x.min = INFINITY;
	bbox.x.max = -INFINITY;
	bbox.y.min = INFINITY;
	bbox.y.max = -INFINITY;
	bbox.z.min = INFINITY;
	bbox.z.max = -INFINITY;
	return (bbox);
}

t_aabb	make_bbox_with_b(t_aabb box1, t_aabb box2)
{
	t_aabb	bbox;

	bbox.x = interval_with_interval(box1.x, box2.x);
	bbox.y = interval_with_interval(box1.y, box2.y);
	bbox.z = interval_with_interval(box1.z, box2.z);
	pad_to_minimums(&bbox);
	return (bbox);
}

t_aabb	make_bbox_with_vec(t_vector a, t_vector b)
{
	t_aabb	bbox;

	if (a.vector[0] <= b.vector[0])
		bbox.x = interval_with_num(a.vector[0], b.vector[0]);
	else
		bbox.x = interval_with_num(b.vector[0], a.vector[0]);
	if (a.vector[1] <= b.vector[1])
		bbox.y = interval_with_num(a.vector[1], b.vector[1]);
	else
		bbox.y = interval_with_num(b.vector[1], a.vector[1]);
	if (a.vector[2] <= b.vector[2])
		bbox.z = interval_with_num(a.vector[2], b.vector[2]);
	else
		bbox.z = interval_with_num(b.vector[2], a.vector[2]);
	pad_to_minimums(&bbox);
	return (bbox);
}

t_aabb	make_bbox_with_interval(
	t_interval x,
	t_interval y,
	t_interval z
)
{
	t_aabb	bbox;

	bbox.x = interval_with_num(x.min, x.max);
	bbox.y = interval_with_num(y.min, y.max);
	bbox.z = interval_with_num(z.min, z.max);
	pad_to_minimums(&bbox);
	return (bbox);
}

t_bool	hit_bbox(t_aabb bbox, t_ray r, t_interval *r_t)
{
	double		t0;
	double		t1;
	int			axis;
	t_interval	ax;
	double		adinv;

	axis = -1;
	while (++axis < 3)
	{
		ax = bbox.vector[axis];
		if (fabs(r.dir.vector[axis]) < 1e-4)
		{
			if (r.orig.vector[axis] < ax.min || r.orig.vector[axis] > ax.max)
				return (false);
		}
		adinv = 1.0 / r.dir.vector[axis];
		t0 = (ax.min - r.orig.vector[axis]) * adinv;
		t1 = (ax.max - r.orig.vector[axis]) * adinv;
		set_ray_interval(t0, t1, r_t);
		if (r_t->max <= r_t->min)
			return (false);
	}
	return (true);
}
