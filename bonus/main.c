/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:34:36 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 14:34:45 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable.h"
#include "camera.h"
#include "texture.h"
#include "bvh_node.h"
#include "hittable_list.h"
#include "wrapper.h"

int	print_frame(t_vars *vars)
{
	if (vars->dirty_c == true || vars->dirty_l == true || vars->dirty_o == true)
	{
		render(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
		vars->dirty_c = false;
		vars->dirty_o = false;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	t_data		data;
	t_camera	camera;

	if (argv[1] == NULL || argc != 2)
	{
		ft_putendl_fd("Usage: ./minirt <scene_file>", 2);
		return (1);
	}
	vars = (t_vars){0};
	vars.camera = &camera;
	vars.data = &data;
	vars.dirty_c = true;
	if (initialize(&vars, argv[1]) < 0)
		return (1);
	vars.light_idx = 0;
	mlx_key_hook(vars.win, key_hooks, &vars);
	mlx_mouse_hook(vars.win, mouse_hooks, &vars);
	mlx_hook(vars.win, 17, 1L << 17, destroy_exit, &vars);
	mlx_loop_hook(vars.mlx, print_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
