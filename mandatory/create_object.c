/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:47:32 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/08/18 11:18:30 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"
#include "texture.h"
#include "wrapper.h"
#include "parser.h"

t_texture	*get_texture(char *token)
{
	char		*tex_name;
	t_texture	*tex;
	t_color		color;

	tex = NULL;
	if (ft_strncmp(token, "tex:", 4) == 0 && ft_strlen(token) > 4)
	{
		tex_name = ft_strchr(token, ':') + 1;
		if (ft_strncmp(tex_name, "checker", 8) == 0)
			tex = make_texture_checker(\
			(t_vector){0, 0, 0}, (t_vector){255, 255, 255}, 10);
		else if (is_readable_file(tex_name) > 0)
			tex = make_texture_image(tex_name);
	}
	else
		tex = make_texture_solid(parse_vector(token));
	return (tex);
}

t_hittable	*create_sphere_object(
	char *tex_token,
	t_vector center,
	double radius)
{
	t_texture	*tex;
	t_texture	*bump;
	t_hittable	*sp;

	tex = get_texture(tex_token);
	bump = NULL;
	if (!tex)
		return (NULL);
	if (get_bumpmap(tex_token, &bump) < 0)
	{
		tex->f.free(tex);
		return (NULL);
	}
	sp = make_wrapper(\
	center, (t_vector){0, 1, 0}, (t_vector){radius, radius, radius});
	if (!sp)
	{
		ft_putendl_fd("Error: Failed to create sphere.", 2);
		tex->f.free(tex);
		bump->f.free(bump);
		return (NULL);
	}
	set_wrapper(sp, get_sphere(), tex, bump);
	return (sp);
}

t_hittable	*create_plane_object(
	char *tex_token,
	t_vector center,
	t_vector normal)
{
	t_texture	*tex;
	t_hittable	*plane;

	tex = get_texture(tex_token);
	if (!tex)
		return (NULL);
	plane = make_plane_wrapper(center, normal);
	if (!plane)
	{
		ft_putendl_fd("Error: Failed to create plane.", 2);
		tex->f.free(tex);
		return (NULL);
	}
	set_plane_wrapper(plane, tex);
	return (plane);
}

t_hittable	*create_cylinder_object(
	char *tex_token,
	t_vector center,
	t_vector normal,
	double dval[2])
{
	t_texture	*tex;
	t_texture	*bump;
	t_hittable	*cy;

	tex = get_texture(tex_token);
	bump = NULL;
	if (!tex)
		return (NULL);
	if (get_bumpmap(tex_token, &bump) < 0)
	{
		tex->f.free(tex);
		return (NULL);
	}
	cy = make_wrapper(center, normal, (t_vector){dval[0], dval[1], dval[0]});
	if (!cy)
	{
		ft_putendl_fd("Error: Failed to create cylinder.", 2);
		tex->f.free(tex);
		bump->f.free(bump);
		return (NULL);
	}
	set_wrapper(cy, get_cylinder(), tex, bump);
	return (cy);
}
