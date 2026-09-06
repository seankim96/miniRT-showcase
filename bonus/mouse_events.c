/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:24 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 14:31:04 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable.h"
#include "hittable_list.h"
#include "camera.h"

void	pick_obj(int x, int y, t_vars *vars)
{
	t_hit_record	rec;
	t_ray			r;

	rec = (t_hit_record){0};
	r = get_ray(vars->camera->viewport, x, y);
	if (vars->objs_list->base.f.hit(vars->objs_list, r, \
	(t_interval){0.0001, INFINITY}, &rec))
	{
		vars->is_plane = false;
		vars->curr_obj = rec.hittable;
	}
	if (rec.hittable == NULL)
		rec.t = INFINITY;
	if (vars->planes_list->base.f.hit(vars->planes_list, r, \
	(t_interval){0.0001, rec.t}, &rec))
	{
		vars->is_plane = true;
		vars->curr_obj = rec.hittable;
	}
}

int	mouse_hooks(int event, int x, int y, void *_vars)
{
	t_vars	*vars;

	vars = (t_vars *)_vars;
	if (event == 1)
		pick_obj(x, y, vars);
	return (0);
}
