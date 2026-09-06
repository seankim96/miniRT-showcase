/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:54:10 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/07/21 13:01:52 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_tokens_length(char **tokens, char *object, int expected_length)
{
	int	len;

	len = get_token_len(tokens);
	if (len != expected_length)
	{
		ft_putstr_fd("Error\nInvalid number of arguments for ", 2);
		ft_putendl_fd(object, 2);
		ft_putstr_fd("Expected ", 2);
		ft_putnbr_fd(expected_length - 1, 2);
		ft_putstr_fd(" arguments, but got ", 2);
		ft_putnbr_fd(len - 1, 2);
		ft_putendl_fd(".", 2);
		return (0);
	}
	return (1);
}
