/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:28:40 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/24 15:24:23 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Iterates the list 'lst' 
and applies the function f to the content of each node
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_temp;

	if (!lst || !f)
		return ;
	lst_temp = lst;
	while (lst_temp)
	{
		f(lst_temp->content);
		lst_temp = lst_temp->next;
	}
}

/*
void version to use with ft_lstiter
** ft_lstiter(lst, &ft_lstolower) (to test) *
*/
// void	ft_lstolower(void *content)
// {
// 	char	*str;
// 	int		i;

// 	str = (char *)content;
// 	i = 0;
// 	while (str[i])
// 	{
// 		str[i] = ft_tolower(str[i]);
// 		i++;
// 	}
// }
