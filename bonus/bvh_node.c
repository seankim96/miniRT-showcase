/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:12:47 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 14:29:44 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable.h"
#include "hittable_list.h"
#include "bvh_node.h"

t_hittable	*make_bvh_s_e(t_hittable **list, int s, int e);

void	bvh_left_right(
	t_bvh_node *node,
	int se[2],
	t_comparator comparator,
	t_hittable **list)
{
	int	s;
	int	e;

	s = se[0];
	e = se[1];
	if ((e - s) == 1)
	{
		list[s]->reference_count += 2;
		node->left = list[s];
		node->right = list[s];
	}
	else if ((e - s) == 2)
	{
		node->left = list[s];
		list[s]->reference_count++;
		node->right = list[s + 1];
		list[s + 1]->reference_count++;
	}
	else
	{
		quick_sort(list, (int [2]){s, e - 1}, \
		sizeof(t_hittable **), comparator);
		node->left = make_bvh_s_e(list, s, s + ((e - s) / 2));
		node->right = make_bvh_s_e(list, s + ((e - s) / 2), e);
	}
}

t_hittable	*make_bvh_s_e(t_hittable **list, int s, int e)
{
	t_aabb			bbox;
	int				i;
	int				axis;
	t_comparator	comparator;
	t_bvh_node		*node;

	node = (t_bvh_node *)ft_calloc(1, sizeof(t_bvh_node));
	node->base.reference_count = 1;
	bbox = make_bbox();
	i = s - 1;
	while (++i < e)
		bbox = make_bbox_with_b(bbox, list[i]->f.bounding_box(list[i]));
	node->bbox = bbox;
	axis = longest_axis(bbox);
	if (axis == 0)
		comparator = x_box_compare;
	else if (axis == 1)
		comparator = y_box_compare;
	else
		comparator = z_box_compare;
	bvh_left_right(node, (int [2]){s, e}, comparator, list);
	node->base.f.hit = hit_bvh;
	node->base.f.bounding_box = bvh_bounding_box;
	node->base.f.free = bvh_free;
	return ((t_hittable *)node);
}

t_bool	hit_empty(void *self, t_ray r, t_interval r_t, t_hit_record *rec)

{
	(void)self;
	(void)r;
	(void)r_t;
	(void)rec;
	return (false);
}

t_hittable	*make_bvh(t_hittable_list *list)
{
	t_bvh_node	*node;

	if (list->size == 0)
	{
		node = (t_bvh_node *)ft_calloc(1, sizeof(t_bvh_node));
		node->bbox = make_bbox();
		node->base.f.hit = hit_empty;
		node->base.f.bounding_box = bvh_bounding_box;
		node->base.f.free = free;
		node->base.reference_count = 0;
		return ((t_hittable *)node);
	}
	node = (t_bvh_node *)make_bvh_s_e(list->hittables, 0, list->size);
	node->base.reference_count = 0;
	return ((t_hittable *) node);
}
