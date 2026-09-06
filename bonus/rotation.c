/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:45:15 by sean              #+#    #+#             */
/*   Updated: 2025/07/21 17:28:33 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "matrix.h"
#include "wrapper.h"

void	apply_min_max(t_aabb *bbox, t_vector vec)
{
	if (vec.x < bbox->x.min)
		bbox->x.min = vec.x;
	if (vec.x > bbox->x.max)
		bbox->x.max = vec.x;
	if (vec.y < bbox->y.min)
		bbox->y.min = vec.y;
	if (vec.y > bbox->y.max)
		bbox->y.max = vec.y;
	if (vec.z < bbox->z.min)
		bbox->z.min = vec.z;
	if (vec.z > bbox->z.max)
		bbox->z.max = vec.z;
}

t_aabb	redifine_bbox(t_aabb local_bbox, t_matrix_4x4 transform)
{
	t_vector	corners[8];
	t_aabb		world_bbox;
	int			i;

	i = -1;
	while (++i < 8)
	{
		corners[i] = (t_vector)
		{.x = local_bbox.x.vector[i % 2], \
		.y = local_bbox.y.vector[(i / 2) % 2], \
		.z = local_bbox.z.vector[(i / 4) % 2]};
	}
	world_bbox = make_bbox_with_vec(corners[0], corners[0]);
	i = -1;
	while (++i < 8)
	{
		corners[i] = matrix_multi_point(corners[i], transform);
		world_bbox.x.min = fmin(world_bbox.x.min, corners[i].x);
		world_bbox.x.max = fmax(world_bbox.x.max, corners[i].x);
		world_bbox.y.min = fmin(world_bbox.y.min, corners[i].y);
		world_bbox.y.max = fmax(world_bbox.y.max, corners[i].y);
		world_bbox.z.min = fmin(world_bbox.z.min, corners[i].z);
		world_bbox.z.max = fmax(world_bbox.z.max, corners[i].z);
	}
	return (world_bbox);
}

int	rotate_cam(t_camera *cam, int axis, t_bool pos)
{
	t_quaternion	q;

	q = (t_quaternion){.x = 0, .y = 0, .z = 0};
	if (pos == true)
		q.list[axis] = D_DELTA;
	else
		q.list[axis] = -D_DELTA;
	q.w = W_DELTA;
	cam->orientation = quaternion_multiple(q, cam->orientation);
	cam->dir = rotate_quaternion(z_vector(), cam->orientation);
	cam->vup = rotate_quaternion(y_vector(), cam->orientation);
	cam->viewport = set_viewport(*cam);
	return (1);
}

int	rotate_obj(void *self, int axis, t_bool pos)
{
	t_wrapper			*wrapper;
	t_transform_info	*trans_info;
	t_quaternion		q;

	wrapper = self;
	trans_info = &wrapper->trans_info;
	q = (t_quaternion){.x = 0, .y = 0, .z = 0};
	if (pos == true)
		q.list[axis] = D_DELTA;
	else
		q.list[axis] = -D_DELTA;
	q.w = W_DELTA;
	trans_info->quat = quaternion_multiple(q, trans_info->quat);
	trans_info->r_quat = quaternion_inverse(trans_info->quat);
	wrapper->update_instance(self);
	return (1);
}
