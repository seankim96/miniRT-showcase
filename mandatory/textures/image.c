/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:12:05 by seungjuk          #+#    #+#             */
/*   Updated: 2025/08/10 15:06:37 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static void	free_image(void *self)
{
	t_image_texture	*tex;

	tex = self;
	free(tex);
}

static t_color	value(void *self, double u, double v, t_vector point)
{
	t_image_texture	*tex;
	unsigned char	*pixel;
	t_color			color;
	int				i;
	int				j;

	tex = self;
	u = fmax(0.0, fmin(1.0, u));
	v = 1.0 - fmax(0.0, fmin(1.0, v));
	i = (u * tex->width);
	j = (v * tex->height);
	pixel = &tex->pixels[j * tex->width * \
	tex->bytes_per_pixel + i * tex->bytes_per_pixel];
	color.x = (double)pixel[0];
	color.y = (double)pixel[1];
	color.z = (double)pixel[2];
	return (color);
}	

t_texture	*make_texture_image(char *filename)
{
	return (NULL);
}
