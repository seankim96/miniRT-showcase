/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:56:36 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:49:36 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*ans;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ans = (char *)ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!ans)
		return (0);
	while (i < s1_len)
	{
		ans[i] = s1[i];
		i++;
	}
	while (i < s1_len + s2_len)
	{
		ans[i] = s2[i - s1_len];
		i++;
	}
	return (ans);
}
