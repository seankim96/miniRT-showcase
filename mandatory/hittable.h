/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:37:14 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 16:49:47 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H

# include "vector.h"
# include "texture.h"
# include "aabb.h"
# include "camera.h"

typedef struct s_viewport	t_viewport;
typedef struct s_hittable	t_hittable;

typedef struct s_hit_record
{
	t_vector	p;
	t_vector	local_p;
	t_vector	normal;
	double		t;
	double		u;
	double		v;
	t_bool		front_face;
	t_texture	*tex;
	t_hittable	*hittable;
}	t_hit_record;

typedef struct s_htable
{
	void		(*resize)(void *self, t_vector change);
	t_vector	(*resize_unit)(t_vector change);
	t_bool
		(*hit)
		(void	*self,
			t_ray	r, t_interval r_t, t_hit_record *rec);
	t_bool
		(*hit_rev)
		(void	*self,
			t_ray	r, t_interval r_t, t_hit_record *rec);
	t_aabb		(*bounding_box)(void *self);
	t_vector
		(*close_point)
		(void	*self, t_vector point);
	void		(*free)(void *hittable);
}	t_htable;

typedef struct s_hittable
{
	t_htable	f;
	int			reference_count;
	t_texture	*tex;
	t_texture	*bump;
	t_aabb		bbox;
}	t_hittable;

void		set_face_normal(t_hit_record *self, \
t_ray r, t_vector outward_normal);
void		default_shape_free(void *self);
t_aabb		default_bounding_box(void *self);

t_hittable	*get_sphere(void);
t_hittable	*get_pillar(void);
t_hittable	*get_circle(void);
t_hittable	*get_cylinder(void);
t_hittable	*get_hyperboloid(void);

#endif
