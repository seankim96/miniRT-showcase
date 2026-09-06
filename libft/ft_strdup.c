/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:24:42 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:39:08 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	slen;
	size_t	i;
	char	*str;

	i = 0;
	slen = ft_strlen(s);
	str = (char *)ft_calloc(slen + 1, sizeof(char));
	if (!str)
		return (0);
	while (i < slen)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
