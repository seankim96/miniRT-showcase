/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:49:05 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:51:35 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable.h"
#include "hittable_list.h"
#include "bvh_node.h"

int	move_objs(t_hittable *obj, int keycode)
{
	if (obj == NULL)
		return (0);
	if (keycode == MINUS)
		return (translate_obj(obj, 2, false));
	if (keycode == PLUS)
		return (translate_obj(obj, 2, true));
	if (keycode == TWO)
		return (translate_obj(obj, 1, false));
	if (keycode == EIGHT)
		return (translate_obj(obj, 1, true));
	if (keycode == SIX)
		return (translate_obj(obj, 0, true));
	if (keycode == FOUR)
		return (translate_obj(obj, 0, false));
	return (0);
}

int	rotate_objs(t_hittable *objs, int keycode)
{
	if (objs == NULL)
		return (0);
	if (keycode == MINUS)
		return (rotate_obj(objs, 2, false));
	if (keycode == PLUS)
		return (rotate_obj(objs, 2, true));
	if (keycode == TWO)
		return (rotate_obj(objs, 1, false));
	if (keycode == EIGHT)
		return (rotate_obj(objs, 1, true));
	if (keycode == FOUR)
		return (rotate_obj(objs, 0, false));
	if (keycode == SIX)
		return (rotate_obj(objs, 0, true));
	return (0);
}

int	resize_objs(t_hittable *curr_obj, int keycode)
{
	if (curr_obj == NULL)
		return (0);
	if (keycode == MINUS)
		return (curr_obj->f.resize(curr_obj, (t_vector){.z = -1}), 1);
	if (keycode == PLUS)
		return (curr_obj->f.resize(curr_obj, (t_vector){.z = 1}), 1);
	if (keycode == TWO)
		return (curr_obj->f.resize(curr_obj, (t_vector){.y = -1}), 1);
	if (keycode == EIGHT)
		return (curr_obj->f.resize(curr_obj, (t_vector){.y = 1}), 1);
	if (keycode == FOUR)
		return (curr_obj->f.resize(curr_obj, (t_vector){.x = -1}), 1);
	if (keycode == SIX)
		return (curr_obj->f.resize(curr_obj, (t_vector){.x = 1}), 1);
	return (0);
}

int	light_etc(t_vars *vars, int keycode)
{
	if (vars->curr_light == NULL)
		return (0);
	if (keycode == MINUS)
	{
		vars->curr_light->tex->f.value_modify(vars->curr_light->tex, true);
		return (1);
	}
	if (keycode == PLUS)
	{
		vars->curr_light->tex->f.value_modify(vars->curr_light->tex, false);
		return (1);
	}
	if (keycode == FOUR)
	{
		vars->curr_light = \
		vars->lights->hittables[abs(--vars->light_idx) % vars->lights->size];
		return (0);
	}
	if (keycode == SIX)
	{
		vars->curr_light = \
		vars->lights->hittables[abs(++vars->light_idx) % vars->lights->size];
		return (0);
	}
	return (0);
}
