/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:46:19 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 16:12:59 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable.h"

void	default_shape_free(void *self)
{
	t_hittable	*hittable;

	hittable = self;
	free(hittable);
}

t_aabb	default_bounding_box(void *self)
{
	t_hittable	*hittable;

	hittable = self;
	return (hittable->bbox);
}

void	set_face_normal(t_hit_record *self, t_ray r, t_vector outward_normal)
{
	if (vector_dot(r.dir, outward_normal) < 0)
		self->front_face = true;
	else
		self->front_face = false;
	if (self->front_face == true)
		self->normal = outward_normal;
	else
		self->normal = vector_scalar(outward_normal, -1);
}
