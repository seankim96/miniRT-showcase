/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:20:06 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/05 18:30:34 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_vars(t_vars *vars, t_data *data)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, X_MAX, Y_MAX, "miniRT");
	data->img = mlx_new_image(vars->mlx, X_MAX, Y_MAX);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
	&data->line_length, &data->endian);
	vars->data = data;
}
