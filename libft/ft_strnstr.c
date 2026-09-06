/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:29:44 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 19:11:40 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	find_len;
	size_t	i;

	if (!big || !little)
		return (0);
	i = 0;
	if (*little == '\0')
		return ((char *)big);
	find_len = ft_strlen(little);
	while (ft_strncmp((big + i), little, find_len) && *big)
		i++;
	if (ft_strncmp((big + i), little, find_len) == 0 && i + find_len <= len)
		return ((char *)(big + i));
	return (0);
}
