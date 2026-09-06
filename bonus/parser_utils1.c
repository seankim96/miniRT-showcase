/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:10:44 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/07/21 15:19:18 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_and_get_next_line(int fd, char **line)
{
	free(*line);
	*line = remove_newline(get_next_line(fd));
}
