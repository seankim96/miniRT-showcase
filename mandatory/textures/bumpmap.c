/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:40:28 by seungjuk          #+#    #+#             */
/*   Updated: 2025/08/10 15:06:31 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bumpmap.h"

static void	free_bump(void *self)
{
	t_bumpmap_texture	*tex;

	tex = self;
	free(tex);
}

static t_color	normal_value(void *self, double u, double v, t_vector point)
{
	t_bumpmap_texture	*tex;
	t_vector			vec;
	int					i;
	int					j;

	tex = self;
	(void)point;
	u = fmax(0.0, fmin(1.0, u));
	v = 1.0 - fmax(0.0, fmin(1.0, v));
	i = fmin(tex->width - 1, u * tex->width);
	j = fmin(tex->height - 1, v * tex->height);
	vec.x = \
	(double)(((unsigned char *)tex->pixels)[j * tex->width + i]) / 255.0;
	vec.y = \
	(double)(((unsigned char *)tex->pixels)[j \
	* tex->width + (int)fmin(i + 1, tex->width - 1)]) / 255.0;
	vec.z = \
	(double)(((unsigned char *)tex->pixels)[(int)fmin(j + 1, tex->height - 1) \
	* tex->width + i]) / 255.0;
	vec = (t_vector){.x = -(vec.x - vec.y), .y = -(vec.x - vec.z), .z = 1};
	vec = vector_unit(vec);
	return (vec);
}

t_texture	*make_bumpmap_image(char *filename)
{
	return (NULL);
}
