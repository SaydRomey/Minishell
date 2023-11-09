/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswitch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:12:56 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 16:08:21 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
find the previous node in the list
return NULL if node is not found or is the head
*/
static t_list	*find_prev_node(t_list *head, t_list *node)
{
	t_list	*curr;

	curr = head;
	while (curr)
	{
		if (curr->next == node)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*
swap nodes when they are next to each other
handles the head case when the first node is swapped
updates pointers to maintain list integrity
*/
void	swap_adjacent_nodes(t_list **head, t_swap *nodes)
{
	if (nodes->prev_a)
		nodes->prev_a->next = nodes->b;
	else
		*head = nodes->b;
	nodes->a->next = nodes->b->next;
	nodes->b->next = nodes->a;
}

/*
swap nodes that are not adjacent
takes care of head case for both nodes
temporary pointer used to avoid loss of list parts
*/
void	swap_non_adjacent_nodes(t_list **head, t_swap *nodes)
{
	t_list	*temp;

	if (nodes->prev_a)
		nodes->prev_a->next = nodes->b;
	else
		*head = nodes->b;
	if (nodes->prev_b)
		nodes->prev_b->next = nodes->a;
	else
		*head = nodes->a;
	temp = nodes->b->next;
	nodes->b->next = nodes->a->next;
	nodes->a->next = temp;
}

/*
node swapping function
calls respective helper function based on adjacency
** uses a t_swap struct *
*/
void	ft_lstswitch(t_list **head, t_list *a, t_list *b)
{
	t_swap	nodes;

	if (!head || !*head || !a || !b || a == b)
		return ;
	nodes.a = a;
	nodes.b = b;
	nodes.prev_a = find_prev_node(*head, a);
	nodes.prev_b = find_prev_node(*head, b);
	if ((!nodes.prev_a && a != *head) || \
		(!nodes.prev_b && b != *head))
		return ;
	if (a->next == b || b->next == a)
	{
		swap_adjacent_nodes(head, &nodes);
	}
	else
	{
		swap_non_adjacent_nodes(head, &nodes);
	}
}
