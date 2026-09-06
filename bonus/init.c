/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:09:09 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/07/21 15:39:40 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "camera.h"
#include "parser.h"
#include "hittable_list.h"
#include "bvh_node.h"

void	init_cam(t_camera *cam, t_vector center, t_vector direction, double fov)
{
	cam->lookfrom = center;
	cam->dir = direction;
	cam->orientation = get_quaternion(cam->dir);
	cam->fov = fov;
	cam->vup = (t_vector){.vector = {0, 1, 0}};
	cam->ratio = 1.0;
	cam->width = X_MAX;
	cam->height = Y_MAX;
	cam->viewport = set_viewport(*cam);
}

int	init_lists(t_vars *vars)
{
	vars->objs = (t_hittable_list *)make_hittable_list(100);
	if (!vars->objs)
	{
		ft_putendl_fd("Error\nFailed to create hittable list.", 2);
		return (-1);
	}
	vars->lights = (t_hittable_list *)make_hittable_list(100);
	if (!vars->lights)
	{
		ft_putendl_fd("Error\nFailed to create hittable list.", 2);
		return (-1);
	}
	vars->objs_list = (t_hittable_list *)make_hittable_list(100);
	if (!vars->objs_list)
	{
		ft_putendl_fd("Error\nFailed to create hittable list.", 2);
		return (-1);
	}
	vars->planes_list = (t_hittable_list *)make_hittable_list(100);
	if (!vars->planes_list)
	{
		ft_putendl_fd("Error\nFailed to create hittable list.", 2);
		return (-1);
	}
	return (0);
}

int	initialize(t_vars *vars, char *filename)
{
	t_hittable	*node;

	if (init_lists(vars) < 0)
		return (-1);
	if (read_file(filename, vars))
	{
		vars->lights->base.f.free(vars->lights);
		vars->objs->base.f.free(vars->objs);
		vars->objs_list->base.f.free(vars->objs_list);
		free(vars->planes_list->hittables);
		free(vars->planes_list);
		return (-1);
	}
	node = make_bvh(vars->objs_list);
	hittable_list_add(vars->objs, node);
	hittable_list_add(vars->objs, (t_hittable *)vars->planes_list);
	init_vars(vars, vars->data);
	vars->curr_light = vars->lights->hittables[0];
	vars->curr_obj = vars->objs_list->hittables[0];
	vars->dirty_c = true;
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
