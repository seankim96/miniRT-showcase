/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:25:21 by sean              #+#    #+#             */
/*   Updated: 2025/07/21 15:28:55 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "raytracing.h"

static t_bool	hit(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	t_generic_wrapper	*wrapper;
	t_transform_info	transform;
	t_ray				local_r;
	t_vector			bump_normal;

	wrapper = self;
	transform = wrapper->base.trans_info;
	local_r.tm = r.tm;
	local_r.orig = matrix_multi_point(r.orig, transform.inv_transform);
	local_r.dir = matrix_multi_vector(r.dir, transform.inv_transform);
	if (wrapper->shape->f.hit(wrapper->shape, local_r, r_t, rec) == false)
		return (false);
	if (wrapper->base.base.bump)
		bump_normal = wrapper->base.base.bump->f.value(wrapper->base.base.bump, \
		rec->u, rec->v, (t_vector){0});
	rec->tex = wrapper->base.base.tex;
	rec->local_p = rec->p;
	rec->p = matrix_multi_point(rec->p, transform.transform);
	rec->normal = matrix_multi_vector(rec->normal, \
	matrix_transpose(transform.inv_transform));
	rec->normal = vector_unit(rec->normal);
	if (wrapper->base.base.bump)
		rec->normal = vector_unit(vector_mul(rec->normal, bump_normal));
	set_face_normal(rec, r, rec->normal);
	return (true);
}

static t_aabb	bounding_box(void *self)
{
	t_generic_wrapper	*wrapper;

	wrapper = self;
	return (wrapper->bbox);
}

static t_vector	close_point(void *self, t_vector point)
{
	t_generic_wrapper	*wrapper;
	t_vector			local_point;
	t_vector			closest_local_point;
	t_vector			closest_world_point;

	wrapper = self;
	local_point = \
	matrix_multi_point(point, wrapper->base.trans_info.inv_transform);
	closest_local_point = \
	wrapper->shape->f.close_point(wrapper->shape, local_point);
	closest_world_point = \
	matrix_multi_point(closest_local_point, wrapper->base.trans_info.transform);
	return (closest_world_point);
}

t_hittable	*make_wrapper(t_vector pos, t_vector normal, t_vector scale)
{
	t_generic_wrapper	*wrapper;
	const t_vector		y_vector = (t_vector){.x = 0, .y = 1, .z = 0};

	wrapper = (t_generic_wrapper *)ft_calloc(1, sizeof(t_generic_wrapper));
	wrapper->base.trans_info.scale = scale;
	wrapper->base.trans_info.inv_scale = \
	(t_vector){.x = 1.0 / scale.x, .y = 1.0 / scale.y, .z = 1.0 / scale.z};
	wrapper->base.trans_info.pos = pos;
	wrapper->base.trans_info.quat = \
	quat_from_vec_to_vec(y_vector, normal);
	wrapper->base.trans_info.r_quat = \
	quaternion_inverse(wrapper->base.trans_info.quat);
	wrapper->base.base.f.hit = hit;
	wrapper->base.base.f.free = wrapper_free;
	wrapper->base.base.f.bounding_box = bounding_box;
	wrapper->base.base.f.close_point = close_point;
	return ((t_hittable *)wrapper);
}

void	set_wrapper(
	void *self,
	t_hittable *shape,
	t_texture *tex,
	t_texture *bump)
{
	t_generic_wrapper	*wrapper;

	shape->reference_count++;
	wrapper = self;
	wrapper->shape = shape;
	wrapper->base.base.tex = tex;
	if (tex != NULL)
		tex->reference_count++;
	wrapper->base.base.bump = bump;
	if (bump != NULL)
		bump->reference_count++;
	update_matrix_transform(&wrapper->base.trans_info);
	wrapper->base.update_instance = update_transform;
	wrapper->base.base.f.resize = resize;
	wrapper->bbox = \
	redifine_bbox(shape->f.bounding_box(shape), \
	wrapper->base.trans_info.transform);
}
