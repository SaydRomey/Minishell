/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection_checks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:36:17 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:19:16 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Master function that wether OPEN and CLOSE a file to validate their
 * existence. OR OPEN the file and returns the correct file descriptor no.
 * All of the opening permissions are based on the specified type.
*/
int	ms_open_type(t_lex *token, char *fd_name, int fd_type, bool	check)
{
	int		fd_no;

	if (fd_type == REDIR_IN)
		fd_no = open(fd_name, READ, S_IRUSR);
	else if (fd_type == REDIR_OUT)
		fd_no = open(fd_name, CREATE | READ_WRITE | TRUNCATE, FD_PERMISSION);
	else if (fd_type == REDIR_OUT_A)
		fd_no = open(fd_name, CREATE | READ_WRITE | APPEND, FD_PERMISSION);
	else if (token != NULL && (fd_type == REDIR_HDOC || fd_type == REDIR_HDOC_X)
		&& check == true)
		ms_heredoc_init(token, fd_name, &fd_no, fd_type);
	else if ((fd_type == REDIR_HDOC || fd_type == REDIR_HDOC_X)
		&& check == false)
		fd_no = open(fd_name, READ, S_IRUSR);
	else
		fd_no = ERROR;
	if (check == true && fd_no > 0)
		close(fd_no);
	return (fd_no);
}

/**
 * @brief Opens files, stores the status inside the token node, then close.
 * @note Serves as a warning that a file may not be used for redirection
*/
void	ms_redir_validation(t_lex *token)
{
	if (token == NULL)
		return ;
	while (token != NULL)
	{
		if (token->type >= REDIR__START && token->type <= REDIR__END)
			token->fd_status = ms_open_type(\
			token, token->token, token->type, true);
		if (token->fd_status == REDIR_SIGINT)
		{
			set_exit_status(REDIR_SIGINT);
			return ;
		}
		token = token->next;
	}
	return ;
}
