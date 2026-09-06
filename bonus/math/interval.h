/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:35:09 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:37:53 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

# include "../raytracing.h"

typedef enum e_bool	t_bool;

typedef union u_interval
{
	struct {
		double	min;
		double	max;
	};
	double	vector[2];
}	t_interval;

t_interval	interval_with_num(double min, double max);
t_interval	interval_with_interval(t_interval min, t_interval max);
t_bool		surrounds(t_interval self, double n);
double		interval_size(t_interval interval);
t_bool		contains(t_interval interval, double n);

#endif
