/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:20:10 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 17:05:39 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_list.h"

t_aabb	list_bounding_box(void *self)
{
	t_hittable_list	*list;

	list = (t_hittable_list *)self;
	return (list->bbox);
}

void	hittable_list_free(void *self)
{
	t_hittable_list	*list;
	t_hittable		*elem;

	list = (t_hittable_list *)self;
	while (list->size--)
	{
		elem = list->hittables[list->size];
		elem->reference_count--;
		if (elem->reference_count == 0)
			elem->f.free(elem);
	}
	free(list->hittables);
	free(list);
}

static t_vector	close_point(void *self, t_vector point)
{
	t_vector		close_so_far;
	double			c_s;
	double			t_s;
	t_vector		temp;
	int				i;

	i = 0;
	close_so_far = \
	((t_hittable_list *)self)->hittables[i]->f.close_point(\
	((t_hittable_list *)self)->hittables[i], point);
	c_s = vector_square(vector_sub(point, close_so_far));
	while (++i < ((t_hittable_list *)self)->size)
	{
		temp = \
		((t_hittable_list *)self)->hittables[i]->f.close_point(\
		((t_hittable_list *)self)->hittables[i], point);
		t_s = vector_square(vector_sub(point, temp));
		if (t_s < c_s)
		{
			c_s = t_s;
			close_so_far = temp;
		}
	}
	return (close_so_far);
}

t_bool	hit_list_rev(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	t_hittable_list	*list;
	t_hittable		**hittables;
	int				i;

	i = -1;
	list = (t_hittable_list *)self;
	hittables = list->hittables;
	while (++i < list->size)
	{
		if (hittables[i]->f.hit(hittables[i], r, r_t, rec) == true)
			return (true);
	}
	return (false);
}

t_hittable	*make_hittable_list(int size)
{
	t_hittable_list	*list;

	list = ft_calloc(1, sizeof(t_hittable_list));
	list->bbox = make_bbox();
	list->base.f.close_point = close_point;
	list->base.f.hit = hit_list;
	list->base.f.hit_rev = hit_list_rev;
	list->base.f.bounding_box = list_bounding_box;
	list->base.f.free = hittable_list_free;
	list->size = 0;
	list->max = size;
	list->hittables = ft_calloc(size, sizeof(t_hittable *));
	return ((t_hittable *)list);
}
