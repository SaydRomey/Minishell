/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:13:15 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/03 20:45:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
takes as a parameter a node and frees its 'content'
using the function 'del',
and then frees the node
** the memory of 'next' is not freed *
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*
removes a node from a list (using the function 'del')
and connects the previous node to the next one
(without breaking the chain)
*/
void	ft_lstremoveone(t_list **head, t_list *to_remove, void (*del)(void *))
{
	t_list	*temp;

	if (!head || !*head || !to_remove)
		return ;
	if (*head == to_remove)
	{
		*head = (*head)->next;
		ft_lstdelone(to_remove, del);
		return ;
	}
	temp = *head;
	while (temp->next && temp->next != to_remove)
		temp = temp->next;
	if (temp->next == NULL)
		return ;
	temp->next = temp->next->next;
	ft_lstdelone(to_remove, del);
}
