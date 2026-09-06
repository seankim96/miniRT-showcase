/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:48:45 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:38:57 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H
# include "../raytracing.h"
# define D_DELTA 0.04361938736533600008415945126217
# define W_DELTA 0.99904822158185779823469374605338

typedef union u_quaternion
{
	struct {
		double	x;
		double	y;
		double	z;
		double	w;
	};
	double	list[4];
}				t_quaternion;

t_quaternion	quaternion_multiple(t_quaternion q1, t_quaternion q2);
t_quaternion	quaternion_inverse(t_quaternion q);
t_vector		rotate_quaternion(t_vector vec, t_quaternion q);
t_quaternion	get_quaternion(t_vector r);
t_quaternion	quat_from_vec_to_vec(t_vector start_vec, t_vector dest_vec);

#endif
