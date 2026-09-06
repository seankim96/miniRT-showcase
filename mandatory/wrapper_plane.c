/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:36:41 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:11:06 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "hittable.h"
#include "raytracing.h"

t_vector	closest_point(void *self, t_vector point)
{
	t_plane_wrapper	*plane;
	t_vector		v;
	double			dist;

	plane = self;
	v = vector_sub(point, plane->world_position);
	dist = vector_dot(v, plane->world_normal);
	return (vector_sub(point, vector_scalar(plane->world_normal, dist)));
}

void	update_plane_instance(void *self)
{
	t_plane_wrapper	*plane;
	t_matrix_4x4	inv_transpose;
	const t_vector	x_vec = (t_vector){.vector = {1, 0, 0}};
	const t_vector	y_vec = (t_vector){.vector = {0, 1, 0}};
	const t_vector	z_vec = (t_vector){.vector = {0, 0, 1}};

	plane = self;
	update_matrix_transform(&plane->base.trans_info);
	plane->world_position = (t_vector){
		.x = plane->base.trans_info.transform.m[0][3],
		.y = plane->base.trans_info.transform.m[1][3],
		.z = plane->base.trans_info.transform.m[2][3]
	};
	inv_transpose = matrix_transpose(plane->base.trans_info.inv_transform);
	plane->world_normal = matrix_multi_vector(z_vec, inv_transpose);
	plane->u_axis = matrix_multi_vector(x_vec, \
	plane->base.trans_info.transform);
	plane->v_axis = matrix_multi_vector(y_vec, \
	plane->base.trans_info.transform);
}

t_bool	plane_hit(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	t_plane_wrapper	*plane;
	double			denom;
	double			t;
	t_vector		p_vec;

	plane = self;
	denom = vector_dot(plane->world_normal, r.dir);
	if (fabs(denom) < 1e-4)
		return (false);
	t = vector_dot(vector_sub \
	(plane->world_position, r.orig), plane->world_normal) / denom;
	if (contains(r_t, t) == false)
		return (false);
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->local_p = \
	matrix_multi_point(rec->p, plane->base.trans_info.inv_transform);
	rec->tex = plane->base.base.tex;
	set_face_normal(rec, r, plane->world_normal);
	p_vec = vector_sub(rec->p, plane->world_position);
	rec->u = vector_dot(p_vec, plane->u_axis) / vector_square(plane->u_axis);
	rec->v = vector_dot(p_vec, plane->v_axis) / vector_square(plane->v_axis);
	return (true);
}

void	wrapper_plane_free(void *self)
{
	t_plane_wrapper	*wrapper;
	t_texture		*tex;
	t_texture		*bump;

	wrapper = self;
	tex = wrapper->base.base.tex;
	if (tex)
	{
		tex->reference_count--;
		if (tex->reference_count == 0)
			tex->f.free(tex);
	}
	bump = wrapper->base.base.bump;
	if (bump)
	{
		bump->reference_count--;
		if (bump->reference_count == 0)
			bump->f.free(bump);
	}
	free(wrapper);
}

t_hittable	*make_plane_wrapper(t_vector pos, t_vector normal)
{
	t_plane_wrapper	*wrapper;
	const t_vector	z_vec = (t_vector){.vector = {0, 0, 1}};

	wrapper = (t_plane_wrapper *)ft_calloc(1, sizeof(t_plane_wrapper));
	wrapper->base.base.bbox = make_bbox_with_interval(\
		(t_interval){-INFINITY, INFINITY}, \
		(t_interval){-INFINITY, INFINITY}, \
		(t_interval){-INFINITY, INFINITY} \
	);
	wrapper->base.trans_info.scale = (t_vector){.x = 1, .y = 1, .z = 1};
	wrapper->base.trans_info.inv_scale = (t_vector){.x = 1, .y = 1, .z = 1};
	wrapper->base.trans_info.pos = pos;
	wrapper->base.trans_info.quat = quat_from_vec_to_vec(z_vec, normal);
	wrapper->base.trans_info.r_quat = quaternion_inverse \
	(wrapper->base.trans_info.quat);
	wrapper->base.base.f.hit = plane_hit;
	wrapper->base.base.f.free = wrapper_plane_free;
	wrapper->base.base.f.close_point = closest_point;
	wrapper->base.base.f.bounding_box = default_bounding_box;
	wrapper->base.update_instance = update_plane_instance;
	return ((t_hittable *)wrapper);
}
