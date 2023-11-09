/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_clean-2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:09:12 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 08:51:23 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief From the stored pointer to the command line, allocate memory to
 * only transfer the valid QUOTE token content.
*/
void	ms_token_quote_clean(t_lex *list)
{
	char	*new;
	size_t	i;

	i = 0;
	ms_token_quote_type_selecter(list);
	if (list->type == UNCLOSED_QUOTE)
	{
		list->token = NULL;
		return ;
	}
	while (list->token[i] != '\0')
	{
		if (list->type == D_QUOTE && list->token[i + 1] == '\"')
			break ;
		else if (list->type == S_QUOTE && list->token[i + 1] == '\'')
			break ;
		i++;
	}
	new = ft_alloc(CALLOC, (i + 1), sizeof(*new));
	if (new == NULL)
		return ;
	ft_strlcpy(new, &list->token[1], (i + 1));
	list->token = NULL;
	list->token = new;
	return ;
}

/** -----
 * @brief From the stored pointer to the command line, allocate memory to
 * only transfer the valid META token content.
*/
void	ms_token_meta_clean(t_lex *list)
{
	size_t	i;
	char	*new;
	char	meta;

	i = 0;
	meta = list->token[i];
	while (list->token[i] == meta)
		i++;
	new = ft_alloc(CALLOC, (i + 1), sizeof(*new));
	if (new == NULL)
		return ;
	if (i == 0)
		i++;
	ft_strlcpy(new, list->token, i + 1);
	list->token = new;
	return ;
}

/**
 * @brief From the stored pointer to the command line, allocate memory to
 * only transfer the valid TEXT token content.
*/
void	ms_token_text_clean(t_lex *list)
{
	char	*new;
	size_t	i;

	i = 0;
	ms_skip_text(list->token, &i);
	new = ft_alloc(CALLOC, (i + 1), sizeof(*new));
	if (new == NULL)
		return ;
	ft_strlcpy(new, list->token, i + 1);
	list->token = NULL;
	list->token = new;
	return ;
}

/**
 * @brief From the stored pointer to the command line, allocate memory to
 * only transfer the valid FLAG token content.
*/
void	ms_token_flag_clean(t_lex *list)
{
	char	*new;
	size_t	i;

	i = 0;
	list->type = FLAG;
	while (list->token[i] != '\0'
		&& ms_ismeta(list->token[i]) == false
		&& ft_iswhitespace(list->token[i]) == false
		&& ms_isquote(list->token[i]) == false)
		i++;
	new = ft_alloc(CALLOC, (i + 1), sizeof(*new));
	if (new == NULL)
		return ;
	ft_strlcpy(new, list->token, i + 1);
	list->token = NULL;
	list->token = new;
	return ;
}
