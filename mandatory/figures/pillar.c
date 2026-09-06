/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pillar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:38:51 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:13:32 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

static t_vector	resize_unit(t_vector change)
{
	double	max;

	max = change.x;
	if (fabs(change.z) > fabs(max))
		max = change.z;
	return ((t_vector){.vector = {max, change.y, max}});
}

t_bool	is_quadratic_in(t_ray r, t_interval r_t, double sqrt_d, double *root)
{
	const double	a = r.dir.x * r.dir.x + r.dir.z * r.dir.z;
	const double	h = r.orig.x * r.dir.x + r.orig.z * r.dir.z;
	const double	c = r.orig.x * r.orig.x + r.orig.z * r.orig.z - 1;
	const double	discriminant = h * h - a * c;

	if (discriminant < 0)
		return (false);
	sqrt_d = sqrt(discriminant);
	*root = (-h - sqrt_d) / a;
	if (!contains(r_t, *root))
	{
		*root = (-h + sqrt_d) / a;
		if (!contains(r_t, *root))
			return (false);
	}
	return (true);
}

static t_bool	hit(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	double		root;
	double		m;
	t_vector	outward_normal;
	double		theta;

	(void)self;
	if (is_quadratic_in(r, r_t, 0, &root) == false)
		return (false);
	m = r.orig.y + root * r.dir.y;
	if (m < -1 || m > 1)
		return (false);
	rec->t = root;
	rec->p = ray_at(r, root);
	outward_normal = (t_vector){.vector = {rec->p.x, 0, rec->p.z}};
	set_face_normal(rec, r, vector_unit(outward_normal));
	theta = atan2(rec->p.x, rec->p.z);
	rec->u = (theta + PI) / (2 * PI);
	rec->v = (m + 1) / 2;
	return (true);
}

static t_vector	close_point(void *self, t_vector point)
{
	double		t;
	t_vector	q_axis;
	t_vector	out_dir;

	t = point.y;
	(void)self;
	if (t < -1.0)
		t = -1.0;
	if (t > 1.0)
		t = 1.0;
	q_axis = (t_vector){.vector = {0, t, 0}};
	out_dir = vector_unit(vector_sub(point, q_axis));
	return (vector_add(q_axis, out_dir));
}

t_hittable	*get_pillar(void)
{
	static t_hittable	*pillar;
	t_aabb				bbox;

	if (pillar == NULL)
	{
		pillar = ft_calloc(1, sizeof(t_pillar));
		bbox.x = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
		bbox.y = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
		bbox.z = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
		pillar->bbox = bbox;
		pillar->f.bounding_box = default_bounding_box;
		pillar->f.free = default_shape_free;
		pillar->f.hit = hit;
		pillar->f.close_point = close_point;
		pillar->f.resize_unit = resize_unit;
	}
	return ((t_hittable *)pillar);
}
