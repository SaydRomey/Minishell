/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_types_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:54:40 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 08:44:39 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Specify the type of TEXT for the TOKENS that are not redirections.
*/
void	ms_token_text_type_specifier(t_lex *list)
{
	if (list->previous != NULL && (list->previous->type >= REDIR__START
			&& list->previous->type <= REDIR__END))
	{
		if (list->previous->type == REDIR_HDOC)
			list->type = TEXT_X;
		else
			list->type = TEXT;
	}
	else
		list->type = COMMAND;
	return ;
}

/** -----
 * @brief Specify the type of QUOTATION for the provided TOKEN, whether it's
 * single (int 39) or double quotes (int 34).
*/
void	ms_token_quote_type_selecter(t_lex *list)
{
	if (list->token[0] == '"'
		&& ft_strchr(&list->token[1], list->token[0]) != NULL)
		list->type = D_QUOTE;
	else if (list->token[0] == '\''
		&& ft_strchr(&list->token[1], list->token[0]) != NULL)
		list->type = S_QUOTE;
	else
		list->type = UNCLOSED_QUOTE;
	return ;
}

/** -----
 * @brief Specify the TYPE of redirection for the provided TOKEN.
*/
void	ms_token_redir_type_selecter(t_lex *list)
{
	if (ft_strlen(list->token) > 2)
		list->type = REDIR_INVALID;
	else if (*list->token == '<')
	{
		if (*(list->token + 1) == '<')
			list->type = REDIR_HDOC;
		else
			list->type = REDIR_IN;
	}
	else if (*list->token == '>')
	{
		if (*(list->token + 1) == '>')
			list->type = REDIR_OUT_A;
		else
			list->type = REDIR_OUT;
	}
	return ;
}
