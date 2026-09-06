/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:04:52 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 14:30:01 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_list.h"

void	hittable_list_add(t_hittable_list *list, t_hittable *hittable)
{
	t_hittable	**temp_list;

	hittable->reference_count++;
	if (list->size == list->max)
	{
		temp_list = ft_calloc(list->max * 2, sizeof(t_hittable *));
		list->max = list->max * 2;
		ft_memmove(temp_list, list->hittables, \
		sizeof(t_hittable *) * list->size);
		free(list->hittables);
		list->hittables = temp_list;
	}
	list->hittables[list->size] = hittable;
	list->size++;
	list->bbox = \
	make_bbox_with_b(list->bbox, hittable->f.bounding_box(hittable));
}

t_bool	hit_list(void *self, t_ray r, t_interval r_t, t_hit_record *rec)
{
	t_hittable_list	*list;
	t_hittable		**hittables;
	int				i;
	double			closest_so_far;
	t_bool			hit_anything;

	i = -1;
	list = (t_hittable_list *)self;
	hittables = list->hittables;
	closest_so_far = r_t.max;
	hit_anything = false;
	while (++i < list->size)
	{
		if (hittables[i]->f.hit(hittables[i], r, \
		(t_interval){0.0001, closest_so_far}, rec) == true)
		{
			hit_anything = true;
			rec->hittable = hittables[i];
			closest_so_far = rec->t;
		}
	}
	return (hit_anything);
}
