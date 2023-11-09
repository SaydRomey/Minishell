/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_count_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:40:19 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:50:18 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Parses the character string, identifies all the VALID expandable '$'
 * character, and increments the counter accordingly.
*/
size_t	ms_count_expandable_dollar(char *str_to_expand)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (str_to_expand == NULL)
		return (0);
	while (str_to_expand[i] != '\0')
	{
		if (str_to_expand[i] == '$')
		{
			if (ms_is_valid_expandable(&str_to_expand[i]))
				count++;
			ms_skip_multi_dollar(str_to_expand, &i);
		}
		else
			i++;
	}
	return (count);
}

/** -----
 * @brief Parses the character strings, increments the counter accordingly to
 * VALID non-expandable characters.
*/
size_t	ms_strlen_exclude_expandables(char *str_to_expand)
{
	size_t	i;
	size_t	adjusted_lenght;

	i = 0;
	adjusted_lenght = 0;
	while (str_to_expand[i] != '\0')
	{
		if (ms_is_valid_expandable(&str_to_expand[i]) == true)
			ms_skip_expandable_content(str_to_expand, &i);
		else
		{
			if (str_to_expand[i] != '\0' || str_to_expand[i + 1] == '\0')
				adjusted_lenght++;
			i++;
		}
	}
	return (adjusted_lenght);
}

/** -----
 * @brief Counts the amount of <TEXT> typed tokens until the list is NULL, OR 
 * token is not <PIPE> typed.
*/
size_t	ms_token_text_counter(t_lex *tokens)
{
	size_t	text_type_counter;

	text_type_counter = 0;
	if (tokens == NULL)
		return (text_type_counter);
	while (tokens != NULL
		&& tokens->type != PIPE)
	{
		if (tokens->type == TEXT)
			text_type_counter++;
		tokens = tokens->next;
	}
	return (text_type_counter);
}
