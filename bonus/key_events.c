/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:54:33 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 15:50:22 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable.h"
#include "hittable_list.h"
#include "bvh_node.h"

int	translation(t_vars *vars, int keycode)
{
	if (vars->f_flag != W)
		return (0);
	if (vars->m_flag == 49)
	{
		if (keycode == MINUS)
			return (translate_camera(vars->camera, 2, false));
		if (keycode == PLUS)
			return (translate_camera(vars->camera, 2, true));
		if (keycode == TWO)
			return (translate_camera(vars->camera, 1, false));
		if (keycode == EIGHT)
			return (translate_camera(vars->camera, 1, true));
		if (keycode == SIX)
			return (translate_camera(vars->camera, 0, true));
		if (keycode == FOUR)
			return (translate_camera(vars->camera, 0, false));
	}
	if (vars->m_flag == 50)
		return (move_objs(vars->curr_light, keycode));
	if (vars->m_flag == 51)
		return (move_objs(vars->curr_obj, keycode));
	return (0);
}

int	rotation(t_vars *vars, int keycode)
{
	if (vars->f_flag != Q)
		return (0);
	if (vars->m_flag == 49)
	{
		if (keycode == MINUS)
			return (rotate_cam(vars->camera, 2, false));
		if (keycode == PLUS)
			return (rotate_cam(vars->camera, 2, true));
		if (keycode == TWO)
			return (rotate_cam(vars->camera, 0, true));
		if (keycode == EIGHT)
			return (rotate_cam(vars->camera, 0, false));
		if (keycode == FOUR)
			return (rotate_cam(vars->camera, 1, true));
		if (keycode == SIX)
			return (rotate_cam(vars->camera, 1, false));
	}
	if (vars->m_flag == 50)
		return (rotate_objs(vars->curr_light, keycode));
	if (vars->m_flag == 51)
		return (rotate_objs(vars->curr_obj, keycode));
	return (0);
}

int	etc(t_vars *vars, int keycode)
{
	if (vars->f_flag != E)
		return (0);
	if (vars->m_flag == 49)
	{
		if (keycode == MINUS)
		{
			vars->camera->fov--;
			vars->camera->viewport = set_viewport(*vars->camera);
			return (1);
		}
		if (keycode == PLUS)
		{
			vars->camera->fov++;
			vars->camera->viewport = set_viewport(*vars->camera);
			return (1);
		}
	}
	if (vars->m_flag == 50)
		return (light_etc(vars, keycode));
	if (vars->m_flag == 51 && vars->is_plane == false)
		return (resize_objs(vars->curr_obj, keycode));
	return (0);
}

int	destroy_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	vars->lights->base.f.free(vars->lights);
	vars->objs_list->base.f.free(vars->objs_list);
	vars->objs->base.f.free(vars->objs);
	exit(0);
}

int	key_hooks(int keycode, void *_vars)
{
	t_vars	*vars;

	vars = (t_vars *)_vars;
	if (keycode == ESC)
		destroy_exit((t_vars *)vars);
	if ((rotation((t_vars *)vars, keycode) == 1 || \
	translation((t_vars *)vars, keycode) == 1) || etc((t_vars *)vars, keycode))
	{
		if (vars->is_plane == false)
		{
			vars->objs->hittables[0]->f.free(vars->objs->hittables[0]);
			vars->objs->hittables[0] = make_bvh(vars->objs_list);
			vars->objs->hittables[0]->reference_count++;
		}
		vars->dirty_o = true;
	}
	if (keycode == 49 || keycode == 50 || keycode == 51)
	{
		vars->m_flag = keycode;
	}
	if (keycode == Q || keycode == W || keycode == E)
	{
		vars->f_flag = keycode;
	}
	return (0);
}
