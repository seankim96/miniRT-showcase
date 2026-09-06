/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:41:06 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 14:39:32 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_bool	hit_unit_circle(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	double		t;
	t_vector	p;

	(void)self;
	if (fabs(r.dir.y) < 1e-4)
		return (false);
	t = -r.orig.y / r.dir.y;
	if (!contains(r_t, t))
		return (false);
	p = ray_at(r, t);
	if (p.x * p.x + p.z * p.z > 1.0)
		return (false);
	rec->t = t;
	rec->p = p;
	set_face_normal(rec, r, (t_vector){.vector = {0, 1, 0}});
	rec->u = (p.x + 1) / 2;
	rec->v = (p.z + 1) / 2;
	return (true);
}

t_vector	closest_point_on_unit_circle(void *self, t_vector point)
{
	const t_vector	point_on_plane = {.x = point.x, .y = 0, .z = point.z};

	(void)self;
	if (vector_square(point_on_plane) <= 1.0)
		return (point_on_plane);
	else
		return (vector_unit(point_on_plane));
}

static t_vector	resize_unit(t_vector change)
{
	double	max;

	max = change.x;
	if (fabs(change.y) > fabs(max))
		max = change.y;
	if (fabs(change.z) > fabs(max))
		max = change.z;
	return ((t_vector){.vector = {max, max, max}});
}

t_hittable	*make_circle(void)
{
	t_hittable	*circle;
	t_aabb		bbox;

	circle = ft_calloc(1, sizeof(t_hittable));
	bbox.x = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
	bbox.y = (t_interval){.min = -EPSILON, .max = EPSILON};
	bbox.z = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
	circle->bbox = bbox;
	circle->f.hit = hit_unit_circle;
	circle->f.close_point = closest_point_on_unit_circle;
	circle->f.bounding_box = default_bounding_box;
	circle->f.free = default_shape_free;
	circle->f.resize_unit = resize_unit;
	return (circle);
}

t_hittable	*get_circle(void)
{
	static t_hittable	*circle;

	if (circle == NULL)
		circle = make_circle();
	return (circle);
}
