/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:32:32 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:34:21 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hittable.h"

t_bool	hit_sphere(void *self, t_ray r, t_interval r_t, t_hit_record *rec);

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

static t_vector	close_point(void *self, t_vector point)
{
	(void)self;
	return (vector_unit(point));
}

t_hittable	*get_sphere(void)
{
	static t_hittable		*sphere;
	t_aabb					bbox;

	if (sphere == NULL)
	{
		sphere = (t_hittable *)ft_calloc(1, sizeof(t_hittable));
		sphere->f.bounding_box = default_bounding_box;
		bbox.x = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
		bbox.y = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
		bbox.z = (t_interval){.min = -1 - EPSILON, .max = 1 + EPSILON};
		sphere->bbox = bbox;
		sphere->f.hit = hit_sphere;
		sphere->f.free = default_shape_free;
		sphere->f.close_point = close_point;
		sphere->f.hit_rev = hit_sphere;
		sphere->f.resize_unit = resize_unit;
	}
	return ((t_hittable *)sphere);
}

t_bool	quadradic_in(t_ray r, t_interval r_t, double *root)
{
	double			a;
	double			h;
	double			c;
	double			discriminant;
	double			sqrt_d;

	a = vector_dot(r.dir, r.dir);
	h = vector_dot(r.orig, r.dir);
	c = vector_dot(r.orig, r.orig) - 1;
	discriminant = h * h - a * c;
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

t_bool	hit_sphere(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	double	root;

	(void)self;
	if (quadradic_in(r, r_t, &root) == false)
		return (false);
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	rec->normal = rec->p;
	set_face_normal(rec, r, rec->p);
	rec->u = (atan2(-rec->p.z, rec->p.x) + PI) / (2 * PI);
	rec->v = acos(-rec->p.y) / PI;
	return (true);
}
