/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:12:01 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:49:54 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	slen;
	char	*ans;
	size_t	i;

	i = 0;
	slen = ft_strlen(s);
	ans = (char *)ft_calloc(slen + 1, sizeof(char));
	if (!ans)
		return (0);
	while (i < slen)
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	return (ans);
}
