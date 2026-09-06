/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:49:15 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/08/18 11:18:55 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "hittable_list.h"
#include "parser.h"

int	parse_entity(t_vars *data, char **tokens, t_flags *flags)
{
	if (ft_strncmp(tokens[0], "C", 2) == 0)
		return (set_cam(data, tokens, flags));
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
	{
		if (!(data->lights->size < 1))
		{
			ft_putendl_fd("Error\nmultiple light source definition", 2);
			return (-2);
		}
		return (set_light(data, tokens, flags));
	}
	else if (ft_strncmp(tokens[0], "A", 2) == 0)
		return (set_ambient(data, tokens, flags));
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		return (parse_sphere(data, tokens, data->objs_list));
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		return (parse_plane(data, tokens, data->planes_list));
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		return (parse_cylinder(data, tokens, data->objs_list));
	return (-1);
}

int	parse_file(int fd, t_vars *data, t_flags *flags)
{
	int			ret_val;
	char		*line;
	char		**tokens;

	line = remove_newline(get_next_line(fd));
	while (line)
	{
		if (line[0] == 0)
		{
			free_and_get_next_line(fd, &line);
			continue ;
		}
		tokens = ft_split(line, ' ');
		ret_val = parse_entity(data, tokens, flags);
		if (ret_val == -2)
		{
			free_line_and_token(line, tokens);
			return (0);
		}
		else if (ret_val == -1)
			ft_putendl_fd("Error\nInvalid identifier", 2);
		free_line_and_token(line, tokens);
		line = remove_newline(get_next_line(fd));
	}
	return (1);
}

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ".rt", 4) != 0)
	{
		ft_putendl_fd("Error\ninvalid filename", 2);
		return (-1);
	}
	return (0);
}

int	read_file(char *filename, t_vars *data)
{
	int			fd;
	char		*dot;
	t_flags		flags;

	dot = ft_strrchr(filename, '.');
	if (check_file_extension(filename) == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error\nfailed to open file", 2);
		return (-1);
	}
	ft_memset(&flags, 0, sizeof(t_flags));
	if (!parse_file(fd, data, &flags))
		return (-1);
	if (!flags.is_ambient || !flags.is_camera || !flags.is_light)
	{
		ft_putendl_fd("Error\nMissing required elements\
(camera, light, ambient).", 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
