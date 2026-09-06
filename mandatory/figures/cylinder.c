/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:49:52 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 14:54:45 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hittable_list.h"
#include "../bvh_node.h"
#include "../wrapper.h"

static t_vector	resize_unit(t_vector change)
{
	double	max;

	max = change.x;
	if (fabs(change.z) > fabs(max))
		max = change.z;
	return ((t_vector){.vector = {max, change.y, max}});
}

static t_bool	d_hit(
	double closest_so_far,
	t_ray cap_r,
	t_interval r_t,
	t_hit_record *rec)
{
	t_bool			hit;

	hit = false;
	if (get_pillar()->f.hit(get_pillar(), cap_r, \
	(t_interval){r_t.min, closest_so_far}, rec) == true)
	{
		hit = true;
		closest_so_far = rec->t;
	}
	cap_r.orig.y -= 1;
	if (get_circle()->f.hit(get_circle(), cap_r, \
	(t_interval){r_t.min, closest_so_far}, rec) == true)
	{
		hit = true;
		closest_so_far = rec->t;
		rec->p.y = 1.0;
	}
	cap_r.orig.y += 2;
	if (get_circle()->f.hit(get_circle(), cap_r, \
	(t_interval){r_t.min, closest_so_far}, rec) == true)
	{
		hit = true;
		rec->p.y = -1;
	}
	return (hit);
}

static t_bool	cylinder_hit(
	void *self,
	t_ray r,
	t_interval r_t,
	t_hit_record *rec)
{
	t_bool			hit;
	t_vector		p_on_sphere;

	(void)self;
	hit = false;
	hit = d_hit(r_t.max, r, r_t, rec);
	if (hit == false)
		return (false);
	p_on_sphere = vector_unit(rec->p);
	rec->u = (atan2(p_on_sphere.z, p_on_sphere.x) + PI) / (2.0 * PI);
	rec->v = acos(-p_on_sphere.y) / PI;
	return (hit);
}

t_hittable	*make_cylinder(void)
{
	t_hittable	*list;
	t_bvh_node	*node;

	list = make_hittable_list(2);
	hittable_list_add((t_hittable_list *)list, get_pillar());
	hittable_list_add((t_hittable_list *)list, get_circle());
	list->f.resize_unit = resize_unit;
	list->f.hit = cylinder_hit;
	return ((t_hittable *)list);
}

t_hittable	*get_cylinder(void)
{
	static t_hittable	*cylinder;

	if (cylinder == NULL)
		cylinder = make_cylinder();
	return (cylinder);
}
