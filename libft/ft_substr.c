/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:14 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/17 10:30:30 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*ans;

	slen = ft_strlen(s);
	if (slen < start)
		i = 0;
	else if (slen - start > len)
		i = len;
	else
		i = slen - start;
	ans = (char *)ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (i < len && (int)i < (int)(slen - start))
	{
		ans[i] = s[i + start];
		i++;
	}
	return (ans);
}
