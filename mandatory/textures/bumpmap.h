/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:45:52 by seungjuk          #+#    #+#             */
/*   Updated: 2025/08/10 15:05:36 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUMPMAP_H
# define BUMPMAP_H
# include "../texture.h"

typedef struct s_bumpmap_texture
{
	t_texture		base;
	unsigned char	*pixels;
	int				width;
	int				height;
	int				bytes_per_pixel;
}	t_bumpmap_texture;

#endif
