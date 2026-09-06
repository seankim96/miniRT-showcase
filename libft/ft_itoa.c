/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:07:34 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/16 16:07:43 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(char *c, int n)
{
	if (n == -2147483648)
	{
		*(c++) = '-';
		*(c++) = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		*(c++) = '-';
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(c, n / 10);
		n %= 10;
	}
	while (*c)
		c++;
	if (n < 10)
		*(c++) = n + '0';
}

char	*ft_itoa(int n)
{
	char	*ans;
	size_t	i;
	int		temp_n;

	i = 0;
	temp_n = n;
	if (n < 0)
		i++;
	while (temp_n != 0)
	{
		i++;
		temp_n /= 10;
	}
	ans = (char *)ft_calloc(i, sizeof(char));
	ft_putnbr(ans, n);
	return (ans);
}
