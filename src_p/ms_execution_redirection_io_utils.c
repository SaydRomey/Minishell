/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_redirection_io_utils.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:13:57 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 10:00:44 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Closes all PREVIOUS file descriptors.
*/
void	ms_close_previous_remaining_fd(t_commands *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->pipe[RD] > 0 && cmd->pipe[RD] <= OPEN_MAX)
			cmd->pipe[RD] = close(cmd->pipe[RD]);
		if (cmd->pipe[WR] > 0 && cmd->pipe[WR] <= OPEN_MAX)
			cmd->pipe[WR] = close(cmd->pipe[WR]);
		cmd = cmd->previous ;
	}
	return ;
}

/** -----
 * @brief Closes all NEXT file descriptors.
*/
void	ms_close_next_remaining_fd(t_commands *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->pipe[RD] > 0 && cmd->pipe[RD] <= OPEN_MAX)
			cmd->pipe[RD] = close(cmd->pipe[RD]);
		if (cmd->pipe[WR] > 0 && cmd->pipe[WR] <= OPEN_MAX)
			cmd->pipe[WR] = close(cmd->pipe[WR]);
		cmd = cmd->next;
	}
	return ;
}

/**
 * @brief Closes all PREVIOUS and NEXT file descriptors, from the current
 * command table.
*/
void	ms_close_remaining_fd(t_commands *cmd)
{
	t_commands	*tmp;

	if (cmd->previous != NULL)
	{
		tmp = cmd->previous;
		ms_close_previous_remaining_fd(tmp);
	}
	if (cmd->next != NULL)
	{
		tmp = cmd->next;
		ms_close_next_remaining_fd(tmp);
	}
	return ;
}
