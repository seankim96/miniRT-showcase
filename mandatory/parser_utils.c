/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:24:08 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/07/21 13:42:20 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

double	ft_atod(const char *str)
{
	char	*dot;
	double	result;
	double	i;
	int		sign;

	i = 0.1;
	result = ft_atoi(str);
	dot = ft_strchr(str, '.');
	sign = 1;
	if (result < 0 || *str == '-')
		sign = -1;
	if (dot == NULL)
		return (result);
	dot++;
	while (dot && *dot && ft_isdigit(*dot))
	{
		result += (*dot - '0') * i * sign;
		i = i / 10;
		dot++;
	}
	return (result);
}

t_vector	parse_vector(char *token)
{
	int			len;
	char		**elem;
	t_vector	vec;

	len = 0;
	elem = ft_split(token, ',');
	while (elem[len])
		len++;
	if (len != 3)
	{
		free_split(elem);
		return ((t_vector){NAN, NAN, NAN});
	}
	vec.x = ft_atod(elem[0]);
	vec.y = ft_atod(elem[1]);
	vec.z = ft_atod(elem[2]);
	free_split(elem);
	return (vec);
}

int	get_token_len(char **tokens)
{
	int	len;

	len = 0;
	while (tokens[len])
		len++;
	return (len);
}

void	free_line_and_token(char *line, char **tokens)
{
	free(line);
	free_split(tokens);
}

char	*remove_newline(char *line)
{
	char	*newline;

	if (!line)
		return (line);
	newline = ft_strrchr(line, '\n');
	if (newline)
		*newline = '\0';
	return (line);
}
