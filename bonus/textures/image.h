/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:12:15 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/14 13:47:35 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# define STB_IMAGE_IMPLEMENTATION
# include "../texture.h"
# include "stb_image.h"

typedef struct s_image_texture
{
	t_texture		base;
	unsigned char	*pixels;
	int				width;
	int				height;
	int				bytes_per_pixel;
}	t_image_texture;

#endif
