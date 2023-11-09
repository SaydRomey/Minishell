/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:21:32 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:43:27 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Handles the redirections and signals within the child process.
*/
static void	ms_execute_cmd(t_commands *command_to_exec)
{
	if (command_to_exec == NULL)
		return ;
	command_to_exec->pid = fork();
	if (command_to_exec->pid < CHILD_PROCESS)
	{
		error_status(EXEC_NAME, ERROR_FORK_EXEC, errno);
		return ;
	}
	if (command_to_exec->pid == CHILD_PROCESS)
	{
		child_signals();
		ms_redirect_io(command_to_exec);
		if (command_to_exec->previous == NULL && \
			command_to_exec->infile == NULL && command_to_exec->next != NULL)
		{
			if (command_to_exec->pipe[RD] > STDIN_FILENO && \
				command_to_exec->pipe[RD] <= OPEN_MAX)
				command_to_exec->pipe[RD] = close(command_to_exec->pipe[RD]);
		}
		process_single_command(command_to_exec);
		exit(get_exit_status());
	}
	else
		return ;
}

/** -----
 * @brief Iterates through the t_commands linked list, waits for the command's
 * process ID. Dereferences the master execution exit status to communicate it
 * to the parent process.
*/
static void	ms_exec_wait_process(t_commands *process_cmd, int *pid_exit_status)
{
	int	command_pid_status;

	command_pid_status = DEFAULT;
	while (process_cmd != NULL)
	{
		waitpid(process_cmd->pid, &command_pid_status, IGNORED_PARAM);
		if (process_cmd->pipe[RD] > STDIN_FILENO && \
			process_cmd->pipe[RD] <= OPEN_MAX)
			process_cmd->pipe[RD] = \
			close(process_cmd->pipe[RD]);
		if (process_cmd->pipe[WR] > STDIN_FILENO && \
			process_cmd->pipe[WR] <= OPEN_MAX)
			process_cmd->pipe[WR] = \
			close(process_cmd->pipe[WR]);
		if (WIFEXITED(command_pid_status) > DEFAULT)
			(*pid_exit_status) = WEXITSTATUS(command_pid_status);
		else if (WIFEXITED(command_pid_status) == WRONG_IFEXIT)
			(*pid_exit_status) = EXIT_ERRNO_WRONG_IFEXIT;
		command_pid_status = DEFAULT;
		process_cmd = process_cmd->next;
	}
	return ;
}

/** -----
 * @brief For each command in the command table, this function launches a child
 * process; Waits for each child process to complete. The order of
 * launching and waiting is based on their indexed position in the linked list.
*/
static void	ms_execution_master(t_commands *command_table)
{
	t_commands	*to_execute;
	int			command_status;

	to_execute = command_table;
	command_status = DEFAULT;
	ms_pipe_build(to_execute);
	while (to_execute != NULL)
	{
		ms_execute_cmd(to_execute);
		to_execute = to_execute->next;
	}
	ms_exec_wait_process(command_table, &command_status);
	exit(command_status);
}

/** -----
 * @brief Executes both, single or multiple commands, from builtins to
 * system calls.
*/
void	ms_execution(t_commands *commands_table)
{
	pid_t		execution_pid;
	int			master_exec_status;

	if (ms_exec_is_single(commands_table) == true)
		return ;
	signal(SIGINT, SIG_IGN);
	execution_pid = fork();
	if (execution_pid < CHILD_PROCESS)
	{
		error_status(EXEC_NAME, ERROR_FORK_MASTER_EXEC, errno);
		return ;
	}
	if (execution_pid == CHILD_PROCESS)
		ms_execution_master(commands_table);
	else
		waitpid(execution_pid, &master_exec_status, IGNORED_PARAM);
	if (WIFEXITED(master_exec_status))
		set_exit_status(WEXITSTATUS(master_exec_status));
	return ;
}
