/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:45:16 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/17 11:55:50 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	i = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (size + slen);
	size -= dlen;
	while (i < size -1 && i < slen)
	{
		dest[i + dlen] = src[i];
		i++;
	}
	dest[i + dlen] = '\0';
	return (dlen + slen);
}
