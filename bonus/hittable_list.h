/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:01:59 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:02:37 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

# include "libft.h"
# include "hittable.h"

typedef struct s_hittable_list
{
	t_hittable	base;
	t_hittable	**hittables;
	t_aabb		bbox;
	int			size;
	int			max;
}	t_hittable_list;

t_bool		hit_list(void *self, t_ray ray, \
t_interval ray_t, t_hit_record *rec);
void		hittable_list_add(t_hittable_list *list, t_hittable *hittable);
t_hittable	*make_hittable_list(int size);

#endif
