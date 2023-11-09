/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_redirection_io.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:59:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 09:49:09 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Transfers the STDIN_FILENO to the specified INFILE file name.
*/
int	ms_redir_input_from_file(const char *filename, int type)
{
	int	infile;

	infile = ms_open_type(NULL, (char *)filename, type, false);
	if (infile < 0)
	{
		perror("Error opening input file");
		return (-1);
	}
	ms_dup2(infile, STDIN_FILENO);
	infile = close(infile);
	return (0);
}

/** -----
 * @brief Transfers the STDOUT_FILENO to the specified OUTFILE file name.
*/
int	ms_redir_output_to_file(const char *filename, int type)
{
	int	outfile;

	outfile = ms_open_type(NULL, (char *)filename, type, false);
	if (outfile < 0)
	{
		perror("Error opening output file");
		return (-1);
	}
	ms_dup2(outfile, STDOUT_FILENO);
	outfile = close(outfile);
	return (0);
}

/** -----
 * @brief Depending on the previous token status, manages the reading end
 * of pipe.
*/
static void	ms_redirect_io_previous(t_commands *cmd)
{
	if (cmd->previous != NULL && \
		cmd->infile == NULL)
	{
		ms_dup2(cmd->previous->pipe[RD], STDIN_FILENO);
		cmd->previous->pipe[RD] = close(cmd->previous->pipe[RD]);
	}
	else if (cmd->previous != NULL && \
				cmd->infile != NULL
		&& (cmd->previous->pipe[RD] > 0 && cmd->pipe[RD] <= OPEN_MAX))
		cmd->previous->pipe[RD] = close(cmd->previous->pipe[RD]);
	return ;
}

/** -----
 * @brief Depending on the next token status, manages the writing end of pipe.
*/
static void	ms_redirect_io_next(t_commands *cmd)
{
	if (cmd->next != NULL && cmd->outfile == NULL)
	{
		ms_dup2(cmd->pipe[WR], STDOUT_FILENO);
		cmd->pipe[WR] = close(cmd->pipe[WR]);
	}
	else if (cmd->next != NULL && cmd->outfile != NULL
		&& (cmd->pipe[WR] > 0 && cmd->pipe[WR] <= OPEN_MAX))
		cmd->pipe[WR] = close(cmd->pipe[WR]);
	return ;
}

/**
 * @brief Master function in charge of redirecting data to correct I/O
 * (Pipes, FDs), depending on the redirecting token.
*/
int	ms_redirect_io(t_commands *cmd)
{
	ms_redirect_io_fd(cmd);
	ms_redirect_io_previous(cmd);
	ms_redirect_io_next(cmd);
	ms_close_remaining_fd(cmd);
	return (0);
}
