/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_redirection_io_single.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:27:21 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 10:07:13 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Duplicates the STDIN_FILENO and STDOUT_FILENO of the parent.
*/
static void	ms_dup_io(t_commands *cmd)
{
	ms_dup(STDIN_FILENO, &cmd->pipe[IN]);
	ms_dup(STDOUT_FILENO, &cmd->pipe[OUT]);
	return ;
}

/** -----
 * @brief Reassigns the correct STDIN_FILENO and STDOUT_FILENO to the parent.
*/
static void	ms_reset_io(t_commands *cmd)
{
	if (cmd->infile != NULL)
		ms_dup2(cmd->pipe[IN], STDIN_FILENO);
	cmd->pipe[IN] = close(cmd->pipe[IN]);
	if (cmd->outfile != NULL)
		ms_dup2(cmd->pipe[OUT], STDOUT_FILENO);
	cmd->pipe[OUT] = close(cmd->pipe[OUT]);
	return ;
}

/** -----
 * @brief Executes a single builtin command from the command line.
*/
bool	ms_exec_is_single(t_commands *cmd)
{
	if (cmd == NULL)
		return (false);
	if (cmd->cmd != NULL && \
		cmd->next == NULL && \
		is_valid_builtin(cmd->cmd[0]) != false)
	{
		if (ft_strstr(cmd->cmd[0], EXIT_CUE) != NULL)
			process_single_command(cmd);
		ms_dup_io(cmd);
		ms_redirect_io(cmd);
		process_single_command(cmd);
		ms_reset_io(cmd);
		return (true);
	}
	return (false);
}
