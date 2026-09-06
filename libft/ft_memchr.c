/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:28:55 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:38:26 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;
	unsigned char	target;
	size_t			i;

	mem = (unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (mem[i] == target)
			return ((void *)&mem[i]);
		i++;
	}
	return (0);
}
