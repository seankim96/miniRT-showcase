/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:12:50 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:01:44 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_NODE_H
# define BVH_NODE_H

# include "raytracing.h"
# include "hittable.h"

typedef struct s_bvh_node
{
	t_hittable	base;
	t_hittable	*left;
	t_hittable	*right;
	t_aabb		bbox;
}	t_bvh_node;

t_hittable	*make_bvh(t_hittable_list *list);
t_bool		hit_bvh(void *self, t_ray r, t_interval r_t, t_hit_record *rec);
t_aabb		bvh_bounding_box(void *self);
void		bvh_free(void	*hittable);
t_bool		x_box_compare(void *a, void *b);
t_bool		y_box_compare(void *a, void *b);
t_bool		z_box_compare(void *a, void *b);

#endif
