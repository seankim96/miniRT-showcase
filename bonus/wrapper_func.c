/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:21:26 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:15:56 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

void	resize(void *self, t_vector change)
{
	t_generic_wrapper	*wrapper;

	wrapper = self;
	change = wrapper->shape->f.resize_unit(change);
	wrapper->base.trans_info.scale = \
	vector_add(wrapper->base.trans_info.scale, change);
	wrapper->base.trans_info.inv_scale = \
	(t_vector){.x = 1.0 / wrapper->base.trans_info.scale.x, \
	.y = 1.0 / wrapper->base.trans_info.scale.y, \
	.z = 1.0 / wrapper->base.trans_info.scale.z};
	wrapper->base.update_instance(wrapper);
}

void	update_transform(void *self)
{
	t_generic_wrapper	*wrapper;

	wrapper = self;
	update_matrix_transform(&wrapper->base.trans_info);
	wrapper->bbox = \
	redifine_bbox(wrapper->shape->f.bounding_box(wrapper->shape), \
	wrapper->base.trans_info.transform);
}

void	wrapper_free(void *self)
{
	t_generic_wrapper	*wrapper;
	t_texture			*tex;
	t_texture			*bump;

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
	wrapper->shape->reference_count--;
	if (wrapper->shape->reference_count == 0)
		wrapper->shape->f.free(wrapper->shape);
	free(wrapper);
}
