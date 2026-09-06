/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:55:45 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:11:10 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hittable_list.h"
#include "../bvh_node.h"
#include "../wrapper.h"
#include "../hittable.h"

static t_vector	resize_unit(t_vector change)
{
	double	max;

	max = change.x;
	if (fabs(change.z) > fabs(max))
		max = change.z;
	return ((t_vector){.vector = {max, change.y, max}});
}

static double	get_roots(t_ray r, double *roots)
{
	const double	a = r.dir.x * r.dir.x + \
	r.dir.z * r.dir.z - (r.dir.y * r.dir.y);
	const double	h = r.orig.x * r.dir.x + \
	r.orig.z * r.dir.z - (r.orig.y * r.dir.y);
	const double	c = r.orig.x * r.orig.x + \
	r.orig.z * r.orig.z - (r.orig.y * r.orig.y) - 1;
	const double	discriminant = h * h - a * c;
	double			sqrt_d;

	if (discriminant < 0)
		return (discriminant);
	sqrt_d = sqrt(discriminant);
	roots[0] = (-h - sqrt_d) / a;
	roots[1] = (-h + sqrt_d) / a;
	return (discriminant);
}

t_bool	is_hyperboloid_in(t_ray r, t_interval r_t, double *root)
{
	double	roots[2];
	double	discriminant;

	discriminant = get_roots(r, roots);
	if (discriminant < 0)
		return (false);
	*root = roots[0];
	if (!contains(r_t, (roots[0])))
	{
		if (!contains(r_t, roots[1]))
			return (false);
		*root = roots[1];
	}
	else
	{
		if (contains(r_t, roots[1]))
		{
			if (*root > roots[1])
				*root = roots[1];
		}
	}
	return (true);
}

static t_bool	hit_capped_hyperboloid(
	void *self,
	t_ray r,
	t_interval r_t,
	t_hit_record *rec)
{
	double		root;
	double		m;
	t_vector	outward_normal;
	double		theta;

	if (is_hyperboloid_in(r, r_t, &root) == false)
		return (false);
	m = r.orig.y + root * r.dir.y;
	if (m < -1 || m > 1)
		return (false);
	rec->t = root;
	rec->p = ray_at(r, root);
	outward_normal = (t_vector){.vector = {rec->p.x, -rec->p.y, rec->p.z}};
	set_face_normal(rec, r, vector_unit(outward_normal));
	theta = atan2(rec->p.x, rec->p.z);
	rec->u = (theta + PI) / (2 * PI);
	rec->v = (m + 1) / 2;
	return (true);
}

t_hittable	*get_hyperboloid(void)
{
	t_hittable			*hyperboloid;
	t_aabb				bbox;
	static t_hittable	*hyperboloid_node;
	t_hittable_list		*list;

	if (hyperboloid_node == NULL)
	{
		hyperboloid = ft_calloc(1, sizeof(t_hittable));
		bbox.x = (t_interval){-sqrt(2) - EPSILON, sqrt(2) + EPSILON};
		bbox.y = (t_interval){-1 - EPSILON, 1 + EPSILON};
		bbox.z = (t_interval){-sqrt(2) - EPSILON, sqrt(2) + EPSILON};
		hyperboloid->bbox = bbox;
		hyperboloid->f.bounding_box = default_bounding_box;
		hyperboloid->f.free = default_shape_free;
		hyperboloid->f.hit = hit_capped_hyperboloid;
		list = (t_hittable_list *)make_hittable_list(1);
		hittable_list_add(list, hyperboloid);
		hyperboloid_node = make_bvh(list);
		hyperboloid_node->f.resize_unit = resize_unit;
		list->base.f.free(list);
	}
	return ((t_hittable *)hyperboloid_node);
}
