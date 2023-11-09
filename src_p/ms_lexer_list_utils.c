/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:53:36 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:26:11 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Creates a new t_lex node.
*/
t_lex	*ms_lex_new(char *token, int type)
{
	t_lex	*head;

	head = ft_alloc(CALLOC, 1, sizeof(*head));
	if (head == NULL)
		return (NULL);
	head->token = token;
	head->type = type;
	head->fd_status = OPEN_MAX + 1;
	head->next = NULL;
	head->previous = NULL;
	return (head);
}

/** -----
 * @brief Finds the last node of the t_lex linked list.
*/
t_lex	*ms_lex_last(t_lex *first)
{
	t_lex	*p_lst;

	if (first == NULL)
		return (NULL);
	p_lst = first;
	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	return (p_lst);
}

/** -----
 * @brief Calculates the number of NODES within the t_lex list.
*/
size_t	ms_lex_size(t_lex *list)
{
	size_t	l;

	l = 0;
	if (list == NULL)
		return (l);
	while (list != NULL)
	{
		l++;
		list = list->next;
	}
	return (l);
}

/** -----
 * @brief Adds a new node to the back of t_lex list.
*/
void	ms_lex_addback(t_lex **head, t_lex *new)
{
	t_lex	*p_last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	p_last = ms_lex_last(*head);
	p_last->next = new;
	new->previous = p_last;
	return ;
}
