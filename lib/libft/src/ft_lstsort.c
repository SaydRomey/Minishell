/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:09:39 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/03 20:43:59 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
returns TRUE (1) if all nodes of linked list 'lst' have a non-null content
returns FALSE (0) if at least one node has a null content
*/
static int	ft_lstcheck(t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		if (!curr->content)
			return (FALSE);
		curr = curr->next;
	}
	return (TRUE);
}

/*
sorts the linked list 'lst' in ascending order
based on the comparison function 'cmp_func'
returns a pointer to the sorted list
returns NULL if 'lst' is NULL
or if any node in 'lst' has a null content.
*/
t_list	*ft_lstsort(t_list *lst, t_cmp cmp_func)
{
	t_list	*curr;
	t_list	*next;

	if (!lst || ft_lstcheck(lst) == FALSE)
		return (NULL);
	curr = lst;
	while (curr)
	{
		next = curr->next;
		while (next)
		{
			if (cmp_func(curr, next) > 0)
				ft_lstswap(curr, next);
			next = next->next;
		}
		curr = curr->next;
	}
	return (lst);
}

/*
sorts the linked list 'lst' in place in ascending order
based on the comparison function 'cmp_func'
does nothing if 'lst' is NULL
or if any node in 'lst' has a null content.
** (needs more tests..) *
*/
// void	ft_lstsort_list(t_list *lst, t_cmp cmp_func)
// {
// 	t_list	*curr;
// 	t_list	*next;

// 	if (!lst || ft_lstcheck(lst) == FALSE)
// 		return ;
// 	curr = lst;
// 	while (curr)
// 	{
// 		next = curr->next;
// 		while (next)
// 		{
// 			if (cmp_func(curr, next) > 0)
// 				ft_lstswap(curr, next);
// 			next = next->next;
// 		}
// 		curr = curr->next;
// 	}
// }
