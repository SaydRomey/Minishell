/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:51:41 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 01:07:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
allocates (malloc) and returns a new node of a linked list
'content' is initialized with the value of 'content'
'next' is initialized to NULL
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	if (!content)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new || !content)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
