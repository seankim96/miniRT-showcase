/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:01:27 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:09:57 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include "raytracing.h"

typedef struct s_ttable
{
	t_color	
		(*value)
		(void	*self,
			double	u, double v, t_vector p);
	void
		(*free)
		(void	*self);
	void
		(*value_modify)
		(void	*self, t_bool is_neg);
}	t_ttable;

typedef struct s_texture
{
	t_ttable	f;
	int			reference_count;
}	t_texture;

typedef struct s_solid_texture
{
	t_texture	base;
	t_color		albedo;
}	t_solid_texture;

typedef struct s_checker_texture
{
	t_texture	base;
	t_texture	*even;
	t_texture	*odd;
	double		inv_scale;
}	t_checker_texture;

t_texture	*make_texture_solid(t_color color);
t_texture	*make_texture_image(char *filename);
t_texture	*make_texture_checker(t_color t1, t_color t2, double scale);
t_texture	*make_bumpmap_image(char *filename);

#endif
