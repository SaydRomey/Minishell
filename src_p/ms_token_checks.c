/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:37:37 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:35:26 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Determines if the character/int is META character OR the beginning
/// of a META token.
bool	ms_ismeta(int c)
{
	if (c == '<' || \
		c == '>' || \
		c == '|')
		return (true);
	return (false);
}

/// @brief Determines if the character/int is the beginning of a QUOTE token.
bool	ms_isquote(int c)
{
	if (c == '\'' || \
		c == '\"')
		return (true);
	return (false);
}

/// @brief Determines if the character/int is the beginning of a FLAG token
bool	ms_isflag(int c)
{
	if (c == '-')
		return (true);
	return (false);
}
