/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:47:36 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/17 13:03:04 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (*lst)
	{
		node = (*lst);
		while (node != 0)
		{
			next = node -> next;
			ft_lstdelone(node, del);
			node = next;
		}
	}
	*lst = NULL;
}
