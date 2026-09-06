/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cam_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:28:45 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/08/18 11:03:09 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "camera.h"
#include "wrapper.h"
#include "vector.h"
#include "hittable_list.h"
#include "raytracing.h"

int	set_cam(t_vars *data, char **tokens, t_flags *flags)
{
	double		fov;
	t_vector	direction;
	t_vector	center;

	if (get_token_len(tokens) != 4)
	{
		ft_putendl_fd("Error\ncamera requires 3 arguments", 2);
		return (0);
	}
	center = parse_vector(tokens[1]);
	direction = parse_vector(tokens[2]);
	fov = ft_atod(tokens[3]);
	if (!is_normal_vec(direction) || !is_fov_in_range(fov)
		|| is_inf_vec(center) || is_inf_vec(direction))
	{
		ft_putendl_fd("Error\ncamera contains invalid value", 2);
		return (0);
	}
	flags->is_camera = 1;
	init_cam(data->camera, center, direction, fov);
	return (0);
}

t_hittable	*make_light(t_vector pos, t_color color, double intensity)
{
	t_texture	*tex;
	t_hittable	*light;
	t_wrapper	*wrapper;

	tex = make_texture_solid(vector_scalar(color, intensity));
	if (!tex)
	{
		ft_putendl_fd("Error\nFailed to create light texture", 2);
		return (NULL);
	}
	light = \
	make_wrapper(pos, (t_vector){0, 0, 1}, (t_vector){0.001, 0.001, 0.001});
	if (!light)
	{
		ft_putendl_fd("Error\nFailed to allocate light object", 2);
		return (NULL);
	}
	set_wrapper(light, get_sphere(), tex, NULL);
	return (light);
}

int	set_light(t_vars *data, char **tokens, t_flags *flags)
{
	double		intensity;
	t_vector	pos;
	t_color		color;
	t_hittable	*light;

	if (get_token_len(tokens) != 4)
	{
		ft_putendl_fd("Error\nlight requires 3 arguments", 2);
		return (0);
	}
	pos = parse_vector(tokens[1]);
	intensity = ft_atod(tokens[2]);
	color = parse_vector(tokens[3]);
	if (!is_between_01(intensity) || is_inf_vec(pos)
		|| is_inf_vec(color) || !is_rgb_in_range(color))
	{
		ft_putendl_fd("Error\nlight contains invalid value", 2);
		return (-2);
	}
	flags->is_light = 1;
	light = make_light(pos, color, intensity);
	if (!light)
		return (-2);
	hittable_list_add(data->lights, light);
	return (0);
}

int	set_ambient(t_vars *data, char **tokens, t_flags *flags)
{
	double		ratio;
	t_color		color;

	if (get_token_len(tokens) != 3)
	{
		ft_putendl_fd("Error\nambient requires 2 arguments", 2);
		return (0);
	}
	ratio = ft_atod(tokens[1]);
	color = parse_vector(tokens[2]);
	if (!is_between_01(ratio) || is_inf_vec(color) || !is_rgb_in_range(color))
	{
		ft_putendl_fd("Error\nambient contains invalid value", 2);
		return (0);
	}
	flags->is_ambient = 1;
	data->camera->ambient = vector_scalar(color, ratio);
	return (0);
}
