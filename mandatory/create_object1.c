/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:23:41 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:23:54 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

int	get_bumpmap(char *token, t_texture **bumpmap)
{
	if (ft_strncmp(token, "tex:", 4) == 0 && ft_strlen(token) > 4
		&& ft_strncmp(token + 4, "checker", 8))
	{
		*bumpmap = make_bumpmap_image(token + 4);
		if (!(*bumpmap))
		{
			ft_putstr_fd(\
			"Error\nFailed to allocate memory for bumpmap image", 2);
			ft_putendl_fd("or failed to load image.", 2);
			return (-1);
		}
	}
	return (0);
}
