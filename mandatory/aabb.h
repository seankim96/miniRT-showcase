/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:34:40 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:57:52 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H
# include "raytracing.h"

typedef union u_aabb
{
	struct
	{
		t_interval	x;
		t_interval	y;
		t_interval	z;
	};
	t_interval	vector[3];
}	t_aabb;

t_aabb	make_bbox(void);
t_aabb	make_bbox_with_b(t_aabb box1, t_aabb box2);
t_aabb	make_bbox_with_vec(t_vector a, t_vector b);
t_aabb	make_bbox_with_interval(t_interval x, t_interval y, t_interval z);
int		longest_axis(t_aabb bbox);
t_bool	hit_bbox(t_aabb bbox, t_ray r, t_interval *r_t);
void	pad_to_minimums(t_aabb *self);
int		longest_axis(t_aabb bbox);
void	set_ray_interval(double t0, double t1, t_interval *r_t);
t_aabb	redifine_bbox(t_aabb bbox, t_matrix_4x4 matrix);

#endif
