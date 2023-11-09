/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:25:27 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/09 11:15:49 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
returns TRUE (1) and executes if argument is a builtin
*/
static int	execute_if_builtin(t_commands *cmd_table, t_list *env, char **envp)
{
	if (is_valid_builtin(cmd_table->cmd[0]))
	{
		execute_builtin(cmd_table, env, envp);
		return (TRUE);
	}
	return (FALSE);
}

/*
special feature if 'PATH' is unset
returns TRUE (1) if PATH exists
or prints error message and returns FALSE (0)
*/
static int	check_path(t_commands *cmd_table, t_list *env)
{
	if (access(cmd_table->cmd[0], F_OK) == 0)
		return (TRUE);
	if (!get_var_value(env, "PATH"))
	{
		ms_error_status(cmd_table->cmd[0], ERR_ENOENT, 127);
		ft_fprintf(FD_ERROR, ERR_NOPATH);
		return (FALSE);
	}
	return (TRUE);
}

/*
finds the command path, sets it in the command table,
frees the path list, generates the envp argument for 'execve'
handles invalid command
*/
static void	execute_command(t_commands *cmd_table, t_list *path_list)
{
	cmd_table->cmd_path = get_cmd_path(cmd_table->cmd[0], path_list);
	if (!cmd_table->cmd_path)
		return ;
	if (path_list)
		ft_lstclear(&path_list, free);
	if (cmd_table->cmd_path)
		ms_execve(cmd_table->cmd_path, cmd_table->cmd, get_child_env());
	else if (cmd_table->cmd[0])
		error_status(cmd_table->cmd[0], ERR_BAD_CMD, 127);
}

/*
dispatch function between builtin and command,
*/
void	process_single_command(t_commands *cmd_table)
{
	t_list	*path_list;
	t_list	*env;
	char	**envp;

	path_list = NULL;
	env = get_envlist();
	envp = get_envptr();
	if (cmd_table->cmd)
	{
		if (cmd_table->cmd == NULL)
			return ;
		if (execute_if_builtin(cmd_table, env, envp) == TRUE)
			return ;
		if (check_path(cmd_table, env) == TRUE)
		{
			path_list = get_path_lst(env);
			execute_command(cmd_table, path_list);
		}
		if (path_list)
			ft_lstclear(&path_list, free);
	}
}
