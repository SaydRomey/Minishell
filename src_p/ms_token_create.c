/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:49:52 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 08:48:30 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Creates a NODE, keeping in memory a pointer to the first character
 * of the QUOTE.
*/
void	ms_token_quote_create(t_lex **lexer, char **tmp, size_t *i)
{
	char	*input_reference;
	size_t	j;

	input_reference = (*tmp);
	j = (*i);
	ms_lex_addback(lexer, ms_lex_new(&input_reference[j], TEXT));
	input_reference = ft_strchr(&input_reference[j + 1], input_reference[j]);
	if (input_reference == NULL)
	{
		input_reference = (*tmp);
		while (input_reference[j] != '\0')
			j++;
		(*tmp) = &input_reference[j];
		(*i) = 0;
		return ;
	}
	(*i) = 0;
	(*tmp) = ++input_reference;
	return ;
}

/** -----
 * @brief Creates a NODE, keeping in memory a pointer to the first
 * character of the META character.
*/
void	ms_token_meta_create(t_lex **lexer, char **tmp, size_t *i)
{
	char	*input_reference;
	char	meta_reference;
	size_t	j;

	input_reference = (*tmp);
	j = (*i);
	ms_lex_addback(lexer, ms_lex_new(&input_reference[j], META_C));
	meta_reference = input_reference[j];
	while (input_reference[j] != '\0' 
		&& input_reference[j] == meta_reference)
		j++;
	(*i) = 0;
	(*tmp) = &input_reference[j];
	return ;
}

/** -----
 * @brief Creates a new NODE, keeping in memory a pointer to the FLAG character.
*/
void	ms_token_flag_create(t_lex **lexer, char **tmp, size_t *i)
{
	char	*input_reference;
	size_t	j;

	input_reference = (*tmp);
	j = (*i);
	ms_lex_addback(lexer, ms_lex_new(&input_reference[j], FLAG));
	while (input_reference[j] != '\0'
		&& ms_ismeta(input_reference[j]) == false
		&& ft_iswhitespace(input_reference[j]) == false
		&& ms_isquote(input_reference[j]) == false)
		j++;
	(*i) = 0;
	(*tmp) = &input_reference[j];
	return ;
}

/** -----
 * @brief Creates a new NODE, keeping in memory a pointer to the TEXT character.
*/
void	ms_token_text_create(t_lex **lexer, char **tmp, size_t *i)
{
	char	*input_reference;
	size_t	j;

	input_reference = (*tmp);
	j = (*i);
	ms_lex_addback(lexer, ms_lex_new(&input_reference[j], TEXT));
	ms_skip_text(input_reference, &j);
	(*i) = 0;
	(*tmp) = &input_reference[j];
	return ;
}

/** -----
 * @brief Creates a new NODE, keeping in memory a pointer to the WHITESPACE
 * character.
*/
void	ms_token_whitespace_create(t_lex **lexer, char **tmp, size_t *i)
{
	char	*input_reference;
	size_t	j;

	input_reference = (*tmp);
	j = (*i);
	ms_lex_addback(lexer, ms_lex_new(&input_reference[j], WHITESPACE));
	ms_skip_whitespaces(tmp, &j);
	(*i) = 0;
	(*tmp) = &input_reference[j];
	return ;
}
