/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_redirection_io_fd.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:18:29 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:51:24 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Redirects INPUT from a file descriptor.
*/
static void	ms_redirect_i_fd(t_commands *cmd)
{
	if (cmd->infile != NULL)
	{
		if (cmd->fd_in[FD_STATUS] < 0)
		{
			ms_error_status(cmd->infile, WRONG_INFILE, 1);
			cmd->fd_in[FD_STATUS] = ms_redir_input_from_file(\
			DEV_NULL, cmd->fd_in[FD_TYPE]);
			if (cmd->cmd != NULL)
			{
				ft_free_tab(&cmd->cmd, ft_tablen(cmd->cmd));
				cmd->cmd = NULL;
			}
		}
		else
			cmd->fd_in[FD_STATUS] = ms_redir_input_from_file(\
			cmd->infile, cmd->fd_in[FD_TYPE]);
	}
	return ;
}

/** -----
 * @brief Redirects OUTPUT to a file descriptor.
*/
static void	ms_redirect_o_fd(t_commands *cmd)
{
	if (cmd->outfile != NULL)
	{
		if (cmd->fd_out[FD_STATUS] < 0)
		{
			ms_error_status(cmd->infile, WRONG_OUTFILE, 1);
			if (cmd->cmd != NULL)
			{
				ft_free_tab(&cmd->cmd, ft_tablen(cmd->cmd));
				cmd->cmd = NULL;
			}
		}
		else
			cmd->fd_out[FD_STATUS] = ms_redir_output_to_file(\
			cmd->outfile, cmd->fd_out[FD_TYPE]);
	}
	return ;
}

/** -----
 * @brief Master redirects to INFILE and OUTFILE.
*/
void	ms_redirect_io_fd(t_commands *cmd)
{
	ms_redirect_i_fd(cmd);
	ms_redirect_o_fd(cmd);
	return ;
}
