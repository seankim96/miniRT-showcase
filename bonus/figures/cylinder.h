/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:41:45 by sean              #+#    #+#             */
/*   Updated: 2025/07/22 15:34:31 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "../hittable.h"

typedef struct s_pillar
{
	t_hittable	base;
	t_vector	center;
	t_vector	vertical;
	double		rs;
	double		ri;
	double		r;
	double		h;
	t_aabb		bbox;
}	t_pillar;

#endif
