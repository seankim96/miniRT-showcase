/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:50:17 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:34:45 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "../hittable.h"

typedef struct s_plane_table
{
	t_bool
		(*is_interior)
		(void	*self,
			double	a, double b, t_hit_record *rec);
}	t_plane_table;

typedef struct s_plane
{
	t_hittable		base;
	t_plane_table	f;
	t_vector		origin;
	t_vector		u;
	t_vector		v;
	t_vector		w;
	t_vector		normal;
	double			p_offset;
	t_aabb			bbox;
}	t_plane;

typedef struct s_quad
{
	t_plane		base;
}	t_quad;

typedef struct s_circle
{
	t_plane		base;
	double		rs;
	double		ri;
	double		r;
}	t_circle;

typedef struct s_triangle
{
	t_plane		base;
}	t_triangle;

t_vector	default_close_point(void *self, t_vector point);

#endif
