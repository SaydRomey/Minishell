/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:22:10 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:25:40 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Determines if the TOKEN is subject to be joined with any other
 * adjencent joinable TOKEN.
*/
static bool	ms_lex_isjoinable(t_lex *tmp)
{
	if (tmp == NULL)
		return (false);
	if (tmp->type == TEXT
		|| tmp->type == COMMAND
		|| tmp->type == S_QUOTE
		|| tmp->type == D_QUOTE
		|| tmp->type == FLAG)
		return (true);
	return (false);
}

/**
 * @brief Verifies if the token is followed by another joinable TOKEN, then
 * concatenate both; Then sends the following TOKEN for suppression.
*/
static void	ms_lex_joinquotes(t_lex **list)
{
	t_lex	*tmp;
	char	*copy; 

	if (list == NULL || *list == NULL)
		return ;
	tmp = *list;
	copy = NULL;
	while (tmp != NULL)
	{
		if (ms_lex_isjoinable(tmp)
			&& tmp->next != NULL && ms_lex_isjoinable(tmp->next))
		{
			copy = ft_strdup(tmp->token);
			free(tmp->token);
			tmp->token = NULL;
			tmp->token = ft_strjoin(copy, tmp->next->token);
			free(copy);
			copy = NULL;
			ms_lex_toremove(list, &tmp->next);
		}
		else
			tmp = tmp->next;
	}
	return ;
}

/**
 * @brief Handles the parsing, cleaning and typing actions for each TOKEN.
*/
void	ms_lex_arrange(t_lex **list)
{
	t_lex	*tmp;

	tmp = *list;
	if (list == NULL || *list == NULL)
		return ;
	while (tmp != NULL)
	{
		ms_token_clean(tmp);
		tmp = tmp->next;
	}
	ms_lex_type_specifier(list);
	ms_lex_expansion_process(list);
	ms_lex_joinquotes(list);
	ms_lex_clean(list);
	ms_lex_retype(list);
	return ;
}

/**
 * @brief Iterates throught each character of the input string, determines if
 * the content is a relevant beginning token, stores the character's adress
 * into a generative linked list.
 * @note The pre_lexer() functions does not allocate memory for tokens. It only
 * stores adresses within the character strings.
*/
void	ms_pre_lexer(t_minishell **data, char *input)
{
	size_t			i;
	char			*tmp;
	t_lex			*lexer;

	i = 0;
	tmp = input;
	lexer = NULL;
	if (data == NULL || *data == NULL || input == NULL)
		return ;
	while (tmp[i] != '\0')
	{
		if (ms_isquote(tmp[i]) == true)
			ms_token_quote_create(&lexer, &tmp, &i);
		else if (ms_ismeta(tmp[i]) == true)
			ms_token_meta_create(&lexer, &tmp, &i);
		else if (ft_iswhitespace(tmp[i]) == true)
			ms_token_whitespace_create(&lexer, &tmp, &i);
		else if (ms_isflag(tmp[i]) == true)
			ms_token_flag_create(&lexer, &tmp, &i);
		else
			ms_token_text_create(&lexer, &tmp, &i);
	}
	(*data)->tokens = lexer;
	return ;
}
