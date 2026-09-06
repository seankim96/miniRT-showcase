/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:53:27 by sean              #+#    #+#             */
/*   Updated: 2025/07/19 19:52:51 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "wrapper.h"
#include "camera.h"

int	translate_obj(void *self, int axis, t_bool pos)
{
	t_wrapper			*wrapper;
	t_transform_info	*trans_info;
	t_vector			vec;

	wrapper = self;
	trans_info = &wrapper->trans_info;
	vec = (t_vector){0};
	if (pos == true)
		vec.vector[axis] = 1;
	else
		vec.vector[axis] = -1;
	trans_info->pos = vector_add(trans_info->pos, vec);
	wrapper->update_instance(self);
	return (1);
}

int	translate_camera(t_camera *cam, int axis, t_bool pos)
{
	t_vector			vec;

	vec = (t_vector){0};
	if (pos == true)
		vec.vector[axis] = 1;
	else
		vec.vector[axis] = -1;
	cam->lookfrom = vector_add(cam->lookfrom, vec);
	cam->viewport = set_viewport(*cam);
	return (1);
}
