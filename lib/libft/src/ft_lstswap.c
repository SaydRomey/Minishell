/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:17:55 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/03 21:36:27 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
swaps the contents of two nodes of a linked list
if one of the nodes is NULL, does nothing
*/
void	ft_lstswap(t_list *a, t_list *b)
{
	void	*tmp;

	if (!a || !b)
		return ;
	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

/*
swaps two adjacent nodes 'a' and 'b' in a linked list
assumes that 'a' comes before 'b' in the list
if either of the nodes is NULL, or if 'a' does not precede 'b', does nothing
** ('head' should be the address of the pointer to the head of the list) *
** to test... (swapping nodes, contents or pointers...?) **
*/
// void	ft_lstswap_nodes(t_list **head, t_list *a, t_list *b)
// {
// 	t_list	*prev;
// 	t_list	*tmp;

// 	if (!head || !(*head) || !a || !b || a->next != b)
// 		return ;
// 	prev = NULL;
// 	tmp = *head;
// 	while (tmp && tmp != a)
// 	{
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	if (prev)
// 		prev->next = b;
// 	else
// 		*head = b;
// 	a->next = b->next;
// 	b->next = a;
// }
