/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_skip_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:56:57 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 10:09:35 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Iterates into the character strings to skips a quote's content.
 * Finds the corresponding closing QUOTATION character, dereferences
 * the index pointer.
*/
void	ms_skip_quote(char *s, size_t *i)
{
	char	quote_reference;

	if (s == NULL || \
		i == NULL)
		return ;
	quote_reference = s[(*i)++];
	while (s[*i] != '\0'
		&& s[*i] != quote_reference)
		(*i)++;
	return ;
}

/** -----
 * @brief If the content following a DOLLARSIGN meet the requirements,
 * DOES NOT handles META characters at this point.
 * @note NOT the same as the close_dollarsign().
*/
void	ms_skip_expandable_content(char *content, size_t *i)
{
	if (content == NULL || i == NULL)
		return ;
	while (ms_is_expandable_content(&content[(*i)]) == true)
		(*i)++;
	(*i)++;
	return ;
}

/** -----
 * @brief Iterates into the character strings until the dereferenced pointer
 * does not meet the text requirements.
 * Dereferences the index pointer.
*/
void	ms_skip_text(char *s, size_t *i)
{
	if (s == NULL || \
		i == NULL)
		return ;
	while (s[*i] != '\0' && \
		ft_iswhitespace(s[*i]) == false && \
		ms_ismeta(s[*i]) == false && \
		ms_isquote(s[*i]) == false)
		(*i)++;
	return ;
}

/** -----
 * @brief Iterates into the character strings until the dereferenced pointer
 * does not meet the whitespace(s) requirement(s).
 * Dereferences the index pointer.
*/
void	ms_skip_whitespaces(char **tmp, size_t *i)
{
	while ((*tmp)[*i] != '\0' && \
		ft_iswhitespace((*tmp)[*i]) == true)
		(*i)++;
	return ;
}
