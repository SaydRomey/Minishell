/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:59:15 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:33:22 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates new links between the previous and following NODES,
 * before destroying the specified node to delete.
*/
void	ms_lex_node_detach(t_lex **list, t_lex *remove)
{
	if (list == NULL || *list == NULL || remove == NULL)
		return ;
	if (remove->previous == NULL)
	{
		if (remove->next != NULL)
		{
			remove->next->previous = NULL;
			(*list) = remove->next;
		}
	}
	if (remove->previous != NULL)
	{
		if (remove->next != NULL)
		{
			remove->previous->next = remove->next;
			remove->next->previous = remove->previous;
		}
		else
			remove->previous->next = NULL;
	}
	return ;
}

/**
 * @brief Manages the proper detaching and destroying actions.
*/
void	ms_lex_node_remove(t_lex **list, t_lex **remove)
{
	if (list == NULL || (*list) == NULL
		|| remove == NULL || *remove == NULL)
		return ;
	ms_lex_node_detach(list, *remove);
	(*remove) = (t_lex *)ms_lex_free_node(remove);
	return ;
}

/** -----
 * @brief Manages if the NODE to remove is the last from the list. Also
 * makes sure to not lose track of the list's head.
*/
void	ms_lex_toremove(t_lex **list, t_lex **toremove)
{
	t_lex	*remove;

	if (list == NULL || *list == NULL)
		return ;
	remove = (*toremove);
	if (*list == remove && remove->next == NULL)
	{
		ms_lex_free(list);
		return ;
	}
	(*toremove) = remove->next;
	ms_lex_node_remove(list, &remove);
	return ;
}

/** -----
 * @brief Removes irrelevant WHITESPACE and/or UNCLOSED_QUOTES typed tokens.
*/
void	ms_lex_clean(t_lex **list)
{
	t_lex	*tmp;

	if (list == NULL || *list == NULL)
		return ;
	tmp = (*list);
	while (*list != NULL && tmp != NULL)
	{
		if (tmp->type == WHITESPACE || tmp->type == UNCLOSED_QUOTE)
			ms_lex_toremove(list, &tmp);
		else
			tmp = tmp->next;
	}
	return ;
}
