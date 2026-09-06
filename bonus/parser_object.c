/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:27:01 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/08/10 15:04:09 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "texture.h"
#include "wrapper.h"
#include "hittable_list.h"
#include <libft.h>
#include <stdio.h>

int	parse_sphere(t_vars *data, char **tokens, t_hittable_list *list)
{
	t_vector	center;
	double		radius;
	t_color		color;
	t_hittable	*sp;

	if (check_tokens_length(tokens, "Sphere", 4) == 0)
		return (0);
	center = parse_vector(tokens[1]);
	radius = ft_atod(tokens[2]) / 2;
	color = parse_vector(tokens[3]);
	if (radius <= 0 || is_inf_vec(center)
		|| !is_valid_texture(tokens[3]))
	{
		ft_putendl_fd("Error\nSphere contains invalid value", 2);
		return (0);
	}
	sp = create_sphere_object(tokens[3], center, radius);
	if (!sp)
		return (-2);
	hittable_list_add(list, sp);
	return (0);
}

int	parse_plane(t_vars *data, char **tokens, t_hittable_list *list)
{
	t_vector	center;
	t_vector	normal;
	t_color		color;
	t_hittable	*pl;

	if (check_tokens_length(tokens, "Plane", 4) == 0)
		return (0);
	center = parse_vector(tokens[1]);
	normal = parse_vector(tokens[2]);
	color = parse_vector(tokens[3]);
	if (!is_normal_vec(normal) || is_inf_vec(center)
		|| is_inf_vec(normal) || !is_valid_texture(tokens[3]))
	{
		ft_putendl_fd("Error\nPlane contains invalid value", 2);
		return (0);
	}
	pl = create_plane_object(tokens[3], center, normal);
	if (!pl)
		return (-2);
	hittable_list_add(list, pl);
	return (0);
}

int	parse_cylinder(t_vars *data, char **tokens, t_hittable_list *list)
{
	t_vector	center;
	t_vector	normal;
	double		dval[2];
	t_color		color;
	t_hittable	*cy;

	if (check_tokens_length(tokens, "Cylinder", 6) == 0)
		return (0);
	center = parse_vector(tokens[1]);
	normal = parse_vector(tokens[2]);
	dval[0] = ft_atod(tokens[3]) / 2;
	dval[1] = ft_atod(tokens[4]);
	color = parse_vector(tokens[5]);
	if (dval[0] <= 0.0 || dval[1] <= 0.0 || !is_normal_vec(normal)
		|| is_inf_vec(center) || is_inf_vec(normal)
		|| !is_valid_texture(tokens[5]))
	{
		ft_putendl_fd("Error\ncylinder contains invalid value", 2);
		return (0);
	}
	cy = create_cylinder_object(tokens[5], center, normal, dval);
	if (!cy)
		return (-2);
	hittable_list_add(list, cy);
	return (0);
}

int	parse_hyperboloid(t_vars *data, char **tokens, t_hittable_list *list)
{
	t_vector	center;
	t_vector	normal;
	double		dval[2];
	t_color		color;
	t_hittable	*hy;

	if (check_tokens_length(tokens, "Hyperboloid", 6) == 0)
		return (0);
	center = parse_vector(tokens[1]);
	normal = parse_vector(tokens[2]);
	dval[0] = ft_atod(tokens[3]) / 2;
	dval[1] = ft_atod(tokens[4]);
	color = parse_vector(tokens[5]);
	if (dval[0] <= 0.0 || dval[1] <= 0.0 || is_inf_vec(center)
		|| is_inf_vec(normal) || !is_valid_texture(tokens[5]))
	{
		ft_putendl_fd("Error\nHyperboloid contains invalid value", 2);
		return (0);
	}
	hy = create_hyperboloid_object(tokens[5], center, normal, dval);
	if (!hy)
		return (-2);
	hittable_list_add(list, hy);
	return (0);
}
