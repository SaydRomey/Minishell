/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:30:11 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:44:21 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Adapted dup() function for minishell.
void	ms_dup(int to_dup, int *store)
{
	int	dup_status;

	if (store == NULL)
		exit (1);
	dup_status = dup(to_dup);
	if (dup_status < 0)
	{
		destroy_all();
		error_status(EXEC_NAME, ERROR_DUP, errno);
		dup_status = 0;
		exit (errno);
	}
	(*store) = dup_status;
	return ;
}

/// @brief Adapted dup2() function for minishell.
void	ms_dup2(int to_dup, int fd)
{
	int	status;

	if (to_dup < 0 || fd < 0)
		return ;
	status = dup2(to_dup, fd);
	if (status < 0)
	{
		destroy_all();
		error_status(EXEC_NAME, ERROR_DUP_TO, errno);
		status = DEFAULT;
		to_dup = close(to_dup);
		exit(errno);
	}
	return ;
}

/// @brief Adapted execve() function for minishell.
void	ms_execve(char *command, char **cmd_param, char **envp)
{
	int	status;

	if (command == NULL || cmd_param == NULL || envp == NULL)
		return ;
	status = execve(command, cmd_param, envp);
	if (status < 0)
	{
		error_status(EXEC_NAME, ERROR_EXECVE, errno);
		status = DEFAULT;
		exit(errno);
	}
	return ;
}
