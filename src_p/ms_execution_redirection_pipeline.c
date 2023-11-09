/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_pipeline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:01:18 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/30 10:30:23 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Builds pipe for each command table, except the last one since it only
 * reads on the previous command table's pipe's reading end, and outputs wether
 * in an outfile, of the standard output.
*/
void	ms_pipe_build(t_commands *cmd)
{
	if (cmd == NULL)
		return ;
	while (cmd != NULL && cmd->next != NULL)
	{
		if (pipe(cmd->pipe) != 0)
		{
			ms_close_previous_remaining_fd(cmd);
			ms_error_status(cmd->cmd[0], ERROR_PIPE_CREATION, errno);
			exit (errno);
		}
		cmd = cmd->next;
	}
	return ;
}
