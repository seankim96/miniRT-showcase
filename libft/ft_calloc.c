/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:03:28 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/19 18:31:48 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned long long	int_max;
	void				*ptr;

	int_max = 2147483647;
	if (nmemb == 0 || size == 0)
	{
		ptr = (void *)malloc(0);
		nmemb = 1;
		size = 1;
	}
	else if (nmemb > int_max || size > int_max)
		return (0);
	else
		ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
