/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_node_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:18:58 by sean              #+#    #+#             */
/*   Updated: 2025/07/21 15:55:41 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_node.h"

t_bool	hit_bvh(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	t_bvh_node	*node;
	t_bool		hit_left;
	t_bool		hit_right;

	node = (t_bvh_node *)self;
	if (hit_bbox(node->bbox, r, &r_t) == false)
		return (false);
	hit_left = node->left->f.hit(node->left, r, r_t, rec);
	if (hit_left == true)
		r_t.max = rec->t;
	hit_right = node->right->f.hit(node->right, r, r_t, rec);
	return (hit_left || hit_right);
}

t_aabb	bvh_bounding_box(void *self)
{
	t_bvh_node	*node;

	node = (t_bvh_node *)self;
	return (node->bbox);
}

void	bvh_free(void *hittable)
{
	t_bvh_node	*node;

	node = (t_bvh_node *)hittable;
	node->left->reference_count--;
	if (node->left->reference_count == 0)
		node->left->f.free(node->left);
	node->right->reference_count--;
	if (node->right->reference_count == 0)
		node->right->f.free(node->right);
	free(node);
}
