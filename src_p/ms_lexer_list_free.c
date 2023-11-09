/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_list_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:57:12 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:28:46 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Destroys a token NODE, by freeing it's content, resetting
 * all it's values to <0>;<NULL>. Then the NODE itself is freed.
*/
void	*ms_lex_free_node(t_lex **node)
{
	if (node == NULL || *node == NULL)
		return (NULL);
	(*node)->next = NULL;
	(*node)->previous = NULL;
	if ((*node)->type != REFERENCE
		&& (*node)->type != WHITESPACE
		&& (*node)->type != UNCLOSED_QUOTE)
		free((*node)->token);
	(*node)->token = NULL;
	(*node)->type = DEFAULT;
	free(*node);
	*node = NULL;
	return (NULL);
}

/**
 * @brief Iterates through the tokens, from START to END, for each node to be
 * properly destroyed.
*/
void	ms_lex_free(t_lex **list)
{
	t_lex	*tmp;
	t_lex	*to_remove;

	tmp = NULL;
	if (list == NULL || *list == NULL)
		return ;
	tmp = *list;
	while (tmp != NULL)
	{
		to_remove = tmp;
		tmp = tmp->next;
		ms_lex_free_node(&to_remove);
		to_remove = NULL;
	}
	*list = NULL;
	return ;
}
