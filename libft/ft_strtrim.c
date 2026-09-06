/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:03:51 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 19:24:15 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ans;
	size_t	slen;

	while (*s1)
	{
		if (!ft_strchr(set, *s1))
			break ;
		s1++;
	}
	slen = ft_strlen(s1);
	while (slen > 0 && ft_strchr(set, s1[slen - 1]))
		slen--;
	ans = ft_substr(s1, 0, slen);
	return (ans);
}
