/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:41:45 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 08:36:31 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Parse the linked list to accurately define each TOKEN's type.
*/
void	ms_lex_type_specifier(t_lex **lexer)
{
	t_lex	*tmp;

	if (lexer == NULL || \
		*lexer == NULL)
		return ;
	tmp = *lexer;
	while (tmp != NULL)
	{
		if (tmp->type == META_C)
		{
			if (*tmp->token == '|')
				tmp->type = PIPE;
			else if (*tmp->token == '<' || \
					*tmp->token == '>')
				ms_token_redir_type_selecter(tmp);
		}
		else if (tmp->type == TEXT)
			ms_token_text_type_specifier(tmp);
		tmp = tmp->next;
	}
	return ;
}

/** -----
 * @brief Re-specify the type of redirection for TOKENS.
*/
static void	ms_lex_retype_redir(t_lex **lexer, t_lex **token)
{
	if ((*token)->next != NULL && \
		(*token)->type != REDIR_INVALID && \
		(*token)->next->type != PIPE)
	{
		if ((*token)->next->type >= REDIR__START
			&& (*token)->next->type <= REDIR__END)
			(*token)->type = PARSE_ERROR;
		else if ((*token)->type == REDIR_HDOC && \
					(*token)->next->type == S_QUOTE)
		{
			(*token)->next->type = REDIR_HDOC_X;
			ms_lex_toremove(lexer, token);
		}
		else
		{
			(*token)->next->type = (*token)->type;
			ms_lex_toremove(lexer, token);
		}
	}
	else
		(*token)->type = PARSE_ERROR;
	return ;
}

/**
 * @brief Retypes all TOKENS to be able to allocate the right amount of tables.
*/
void	ms_lex_retype(t_lex **lexer)
{
	t_lex	*tmp;

	if (lexer == NULL || \
		(*lexer) == NULL)
		return ;
	tmp = (*lexer);
	while (tmp != NULL)
	{
		if (tmp->type == COMMAND || tmp->type == FLAG || \
			tmp->type == S_QUOTE || tmp->type == D_QUOTE || \
			tmp->type == TEXT_X)
			tmp->type = TEXT;
		if (tmp->type == FLAG)
			tmp->type = TEXT;
		if (tmp->type >= REDIR__START && tmp->type <= REDIR__END)
			ms_lex_retype_redir(lexer, &tmp);
		if (tmp->type == PIPE && (tmp->previous == NULL || \
			tmp->next == NULL))
			tmp->type = PARSE_ERROR;
		if (tmp->type == PIPE && tmp->next != NULL
			&& (tmp->next->type == PIPE || tmp->next->type == PARSE_ERROR))
			tmp->type = PARSE_ERROR;
		tmp = tmp->next;
	}
	return ;
}
