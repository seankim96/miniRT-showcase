/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:06:39 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:50:04 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	target;

	target = (char) c;
	i = ft_strlen(s);
	if (target == '\0')
		return ((char *)&s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == target)
			return ((char *)&s[i]);
	}
	return (0);
}
