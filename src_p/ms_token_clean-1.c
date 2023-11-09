/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_clean-1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:53:48 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 08:56:42 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief WHITESPACE token will be used to determine if TEXT tokens will be
 * joined or not (two TEXT type tokens side by side will, 2 separated by a
 * whitespace token won't).
*/
static void	ms_token_whitespace_clean(t_lex *list)
{
	list->token = NULL;
	list->type = WHITESPACE;
	return ;
}

/**
 * @brief Dispatches the token to the right cleaning function, based on
 * their type.
*/
void	*ms_token_clean(t_lex *list)
{
	size_t	i;

	i = 0;
	if (ms_isquote(list->token[i]) == true)
		ms_token_quote_clean(list);
	else if (ms_ismeta(list->token[i]) == true)
		ms_token_meta_clean(list);
	else if (ms_isflag(list->token[i]) == true)
		ms_token_flag_clean(list);
	else if (ft_iswhitespace(list->token[i]) == true)
		ms_token_whitespace_clean(list);
	else
		ms_token_text_clean(list);
	return (list);
}
