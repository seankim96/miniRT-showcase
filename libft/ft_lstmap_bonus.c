/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:11:47 by seungjuk          #+#    #+#             */
/*   Updated: 2024/10/12 18:38:17 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node_front;
	t_list	*current_node;

	if (!lst)
		return (0);
	node_front = ft_lstnew(f(lst->content));
	if (!node_front)
		return (0);
	current_node = node_front;
	while (lst->next)
	{
		current_node->next = ft_lstnew(f((lst -> next)->content));
		if (!(current_node->next))
		{
			ft_lstclear(&node_front, del);
			return (0);
		}
		current_node = current_node->next;
		lst = lst -> next;
	}
	return (node_front);
}
