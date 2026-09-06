/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:11:55 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 16:12:21 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include "raytracing.h"

typedef t_vector	t_color;
double	linear_to_gamma(double linear_component);
t_color	write_color(t_color	color);

#endif
