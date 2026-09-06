/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_checker_scale_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:34:32 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/08/18 10:49:31 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

double	get_checker_scale(t_object_type type)
{
	if (type == SPHERE)
		return (0.1);
	else if (type == PLANE)
		return (10);
	else if (type == CYLINDER)
		return (0.1);
	return (0.1);
}
