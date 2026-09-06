/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:49:37 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:39:42 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

t_quaternion	quaternion_multiple(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	new_quat;

	new_quat.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	new_quat.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	new_quat.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	new_quat.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (new_quat);
}

t_vector	rotate_quaternion(t_vector vec, t_quaternion q)
{
	t_quaternion	q_vec;
	t_quaternion	q_inv;
	t_quaternion	q_res;

	q_vec.w = 0;
	q_vec.x = vec.x;
	q_vec.y = vec.y;
	q_vec.z = vec.z;
	q_inv.w = q.w;
	q_inv.x = -q.x;
	q_inv.y = -q.y;
	q_inv.z = -q.z;
	q_res = quaternion_multiple(quaternion_multiple(q, \
	q_vec), q_inv);
	return ((t_vector){.x = q_res.x, \
	.y = q_res.y, .z = q_res.z});
}

t_quaternion	get_quaternion(t_vector r)
{
	t_quaternion	quat;

	quat.w = cos(PI / 360 * r.z) * cos(PI / 360 * r.x) * cos(PI / 360 * r.y);
	quat.w += sin(PI / 360 * r.z) * sin(PI / 360 * r.x) * sin(PI / 360 * r.y);
	quat.x = cos(PI / 360 * r.z) * cos(PI / 360 * r.x) * sin(PI / 360 * r.y);
	quat.x -= sin(PI / 360 * r.z) * sin(PI / 360 * r.x) * cos(PI / 360 * r.y);
	quat.y = cos(PI / 360 * r.z) * sin(PI / 360 * r.x) * cos(PI / 360 * r.y);
	quat.y += sin(PI / 360 * r.z) * cos(PI / 360 * r.x) * sin(PI / 360 * r.y);
	quat.z = sin(PI / 360 * r.z) * cos(PI / 360 * r.x) * cos(PI / 360 * r.y);
	quat.z -= cos(PI / 360 * r.z) * sin(PI / 360 * r.x) * sin(PI / 360 * r.y);
	return (quat);
}

t_quaternion	quat_from_vec_to_vec(t_vector start_vec, t_vector dest_vec)
{
	t_vector		axis;
	double			dot;
	t_quaternion	q;
	double			half_angle;

	dot = vector_dot(start_vec, dest_vec);
	if (dot > 0.999999)
		return ((t_quaternion){.w = 1, .x = 0, .y = 0, .z = 0});
	if (dot < -0.999999)
		return ((t_quaternion){.w = 0, .x = 1, .y = 0, .z = 0});
	axis = vector_unit(vector_cross(start_vec, dest_vec));
	half_angle = acos(dot) / 2.0;
	q.w = cos(half_angle);
	q.x = axis.x * sin(half_angle);
	q.y = axis.y * sin(half_angle);
	q.z = axis.z * sin(half_angle);
	return (q);
}

t_quaternion	quaternion_inverse(t_quaternion q)
{
	t_quaternion	inv_q;

	inv_q.w = q.w;
	inv_q.x = -q.x;
	inv_q.y = -q.y;
	inv_q.z = -q.z;
	return (inv_q);
}
