/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_expansion_process.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:34:53 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:29:03 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process expandable '$' within the TOKENS linked list.
*/
void	ms_lex_expansion_process(t_lex **head)
{
	t_lex	*tmp;
	char	*old;

	tmp = *head;
	if (head == NULL || *head == NULL)
		return ;
	while (tmp != NULL)
	{
		if ((tmp->type == TEXT || tmp->type == D_QUOTE || tmp->type == COMMAND)
			&& ms_count_expandable_dollar(tmp->token) > 0)
		{
			old = ft_alloc(CALLOC, (ft_strlen(tmp->token) + 1), sizeof(*old));
			if (old == NULL)
				return ;
			ft_strlcpy(old, tmp->token, (ft_strlen(tmp->token) + 1));
			free(tmp->token);
			tmp->token = NULL;
			tmp->token = ms_expand(old);
			free(old);
			old = NULL;
		}
		tmp = tmp->next;
	}
	return ;
}
