/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:22:34 by sean              #+#    #+#             */
/*   Updated: 2025/07/21 17:12:17 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H
# include "hittable.h"
# include "matrix.h"

typedef struct s_transform_info
{
	t_quaternion		quat;
	t_quaternion		r_quat;
	t_vector			pos;
	t_vector			scale;
	t_vector			inv_scale;
	t_vector			shear_xx_xy_yx;
	t_vector			shear_yz_zx_zz;
	t_matrix_4x4		transform;
	t_matrix_4x4		inv_transform;
}	t_transform_info;

typedef struct s_wrapper
{
	t_hittable			base;
	t_transform_info	trans_info;
	void				(*update_instance)(void *self);
}	t_wrapper;

typedef struct s_generic_wrapper
{
	t_wrapper	base;
	t_hittable	*shape;
	t_aabb		bbox;
}	t_generic_wrapper;

typedef struct s_plane_wrapper
{
	t_wrapper			base;
	t_vector			world_normal;
	t_vector			world_position;
	t_vector			u_axis;
	t_vector			v_axis;
}	t_plane_wrapper;

t_hittable	*make_wrapper(t_vector pos, t_vector normal, t_vector scale);
void		set_wrapper(void *self, t_hittable *shape, \
			t_texture *tex, t_texture *bump);
t_hittable	*make_plane_wrapper(t_vector pos, t_vector normal);
void		set_plane_wrapper(void *self, t_texture *tex);
void		resize(void *self, t_vector change);
void		update_transform(void *self);
void		wrapper_free(void *self);
void		update_plane_instance(void *self);

#endif
