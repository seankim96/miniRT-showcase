/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warpper_plane_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:09:25 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:09:34 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"
#include "hittable.h"
#include "raytracing.h"

void	set_plane_wrapper(void *self, t_texture *tex)
{
	t_plane_wrapper	*wrapper;

	wrapper = self;
	wrapper->base.base.tex = tex;
	if (tex != NULL)
		tex->reference_count++;
	update_plane_instance(wrapper);
}
