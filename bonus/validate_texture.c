/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:07:46 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/07/21 13:38:23 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_number(char *token, int *i)
{
	int	is_dot;

	is_dot = 0;
	if (token[*i] == '-')
		(*i)++;
	while (ft_isdigit(token[*i]) || token[*i] == '.')
	{
		if (is_dot == 0 && token[*i] == '.')
			is_dot = 1;
		else if (is_dot == 1 && token[*i] == '.')
			return (0);
		else if (ft_isdigit(token[*i]) == 0)
			return (0);
		(*i)++;
	}
	return (1);
}

int	is_vector(char *token)
{
	int	i;
	int	index;
	int	is_dot;

	i = 0;
	index = 0;
	while (i < 2)
	{
		if (!is_number(token, &index) || token[index] != ',')
			return (0);
		index++;
		i++;
	}
	if (is_number(token, &index)
		&& (token[index] == '\0' || token[index] == '\n'))
		return (1);
	return (0);
}

int	is_readable_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" is not a readable file or cannot open file.\n", 2);
	}
	close(fd);
	return (fd);
}

int	is_valid_texture(char *token)
{
	t_vector	color;

	if (ft_strncmp(token, "tex:", 4) == 0 && ft_strlen(token) > 4)
	{
		if (ft_strncmp(token + 4, "checker", 8) == 0)
			return (1);
		else if (is_readable_file(token + 4) > 0)
			return (1);
		ft_putendl_fd("Error: Invalid texture file.", 2);
	}
	else if (is_vector(token))
	{
		color = parse_vector(token);
		if (!is_inf_vec(color) && is_rgb_in_range(color))
			return (1);
		ft_putendl_fd("Error: Invalid color format or out of range.", 2);
	}
	return (0);
}
