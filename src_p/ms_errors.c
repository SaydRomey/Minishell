/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:50:40 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:50:31 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Display on the STDERR output the parsing error message.
*/
static void	ms_parse_error_message(t_lex *targeted)
{
	ft_putstr_fd(EXEC_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(ERROR_PARSE_NEAR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(targeted->token, STDERR_FILENO);
	return ;
}

/** -----
 * @brief Iterates through the list of tokens searching for any instance of
 * a <PARSE_ERROR> typed node; Sets the EXIT_STATUS to the correct value.
*/
bool	ms_parse_error(t_lex *tokens)
{
	t_lex	*target;

	target = tokens;
	while (target != NULL)
	{
		if (target->type == PARSE_ERROR)
		{
			ms_parse_error_message(target);
			set_exit_status(EXIT_ERRNO_PARSE);
			target = NULL;
			return (true);
		}
		target = target->next;
	}
	return (false);
}
