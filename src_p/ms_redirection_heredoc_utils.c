/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection_heredoc_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:46:27 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:12:08 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Unlink the temporary HEREDOC file created for the command line
 * execution.
*/
void	ms_close_heredoc(t_lex *token)
{
	while (token != NULL)
	{
		if ((token->type == REDIR_HDOC || token->type == REDIR_HDOC_X)
			&& ((token->fd_status > 0 && token->fd_status < OPEN_MAX)
				|| token->fd_status == REDIR_SIGINT) && token->token != NULL)
		{
			if (token->token != NULL)
			{
				if (unlink(token->token) < 0)
					error_status(EXEC_NAME, ERROR_UNLINK_HDOC, errno);
				free(token->token);
				token->token = NULL;
			}
		}
		token = token->next;
	}
	return ;
}

/** -----
 * @brief Creates the HEREDOC file name <TOKEN.heredoc>
*/
char	*ms_get_heredoc_name(char *fd_name)
{
	char	*name;

	name = NULL;
	name = ft_strjoin(fd_name, HEREDOC_EXT);
	return (name);
}

/** -----
 * @brief Handles the expansion process of the most recent input line from user.
*/
void	ms_heredoc_expansion(char **rl)
{
	char	*expansion;

	expansion = NULL;
	expansion = ft_strdup(*rl);
	free(*rl);
	*rl = NULL;
	*rl = ms_expand(expansion);
	free(expansion);
	expansion = NULL;
	return ;
}
