/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:02:38 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/17 15:34:03 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_arrcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

static char	*ft_allocate(char const *s, size_t *start, char c)
{
	size_t	end;
	char	*str;

	end = 0;
	while (s[*start + end] != c && s[*start + end])
		end++;
	str = ft_substr(s, *start, end);
	*start += end;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	count;
	size_t	start;
	size_t	i;

	i = 0;
	start = 0;
	count = ft_arrcount(s, c);
	arr = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!arr)
		return (0);
	while (i < count)
	{
		while (s[start] == c && s[start])
			start++;
		arr[i] = ft_allocate(s, &start, c);
		if (!arr[i++])
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (0);
		}
	}
	return (arr);
}
