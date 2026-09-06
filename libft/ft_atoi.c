/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:43:35 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:56:20 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	char	*spaces;

	spaces = " \n\t\v\f\r";
	while (*spaces)
	{
		if (*spaces != c)
			spaces++;
		else
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	pos;

	i = 0;
	pos = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			pos = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		i = i * 10 + (*nptr - '0');
		nptr++;
	}
	return (i * pos);
}
