/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:06:47 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/21 01:15:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
handles cases where the content duplication fails
*/
static void	clean_dup(t_list **new_lst, void *new_cont, t_del_fptr del_content)
{
	del_content(new_cont);
	ft_lstclear(new_lst, del_content);
}

/*
adds the duplicated content to the new list
returns the new tail of the list
or NULL if the node creation fails
*/
static t_list	*append_to_list(t_list **new_lst, void *new_cont)
{
	t_list	*new_node;
	t_list	*tail_node;

	new_node = ft_lstnew(new_cont);
	if (!*new_lst)
	{
		*new_lst = new_node;
		return (new_node);
	}
	else
	{
		tail_node = ft_lstlast(*new_lst);
		tail_node->next = new_node;
		return (new_node);
	}
}

/*
returns a 'deep' copy of the linked list
(duplicates both the list structure and the contents)
changes to the content of a list will not reflect in the other
** uses function pointers to copy lists with any content type *
returns NULL if the content duplication fails or if the list is empty
*/
t_list	*ft_lstcpy(t_list *lst, t_dup_fptr dup_cont, t_del_fptr del_cont)
{
	t_list	*new_lst;
	t_list	*tail_node;
	void	*new_cont;

	new_lst = NULL;
	while (lst)
	{
		new_cont = dup_cont(lst->content);
		if (!new_cont)
		{
			ft_lstclear(&new_lst, del_cont);
			return (NULL);
		}
		tail_node = append_to_list(&new_lst, new_cont);
		if (!tail_node)
		{
			clean_dup(&new_lst, new_cont, del_cont);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_lst);
}
