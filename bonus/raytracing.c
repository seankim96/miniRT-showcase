/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:05:00 by seungjuk          #+#    #+#             */
/*   Updated: 2025/06/21 18:06:20 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

// int		r_int(int rand[4])
// {
// 	int t;

// 	t = rand[1];
// 	t ^= t << 11;
// 	t ^= t >> 8;
// 	rand[1] = rand[2];
// 	rand[2] = rand[3];
// 	rand[3] = rand[0];
// 	rand[0] ^= rand[0] >> 19;
// 	rand[0] ^= t;
// 	return (rand[0]);
// }

// t_vector	r_square(int rand[4])
// {
// 	t_vector	vec;

// 	vec.x = r_int(rand) / (INFINITY + 1.0) - 0.5;
// 	vec.y = r_int(rand) / (INFINITY + 1.0) - 0.5;
// 	rand[3]+= 7;
// 	return (vec);
// }
