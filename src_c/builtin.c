/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:35:26 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 18:26:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_secret_builtin(t_commands *cmd_table, t_list *env, char **envp)
{
	char	**args;

	args = cmd_table->cmd;
	if (!ft_strcmp(args[0], "shellv"))
		display_shell_vars(env);
	if (!ft_strcmp(args[0], "reset"))
		reset_env(&env, args, envp);
}

void	execute_builtin(t_commands *cmd_table, t_list *env, char **envp)
{
	char	**args;

	args = cmd_table->cmd;
	if (is_secret_builtin(args[0]))
	{
		exec_secret_builtin(cmd_table, env, envp);
		return ;
	}
	if (ft_strchr(args[0], '=') != NULL)
		assign_var(env, args);
	else if (!ft_strcmp(args[0], "echo"))
		mini_echo(args);
	else if (!ft_strcmp(args[0], "cd"))
		mini_cd(&env, args);
	else if (!ft_strcmp(args[0], "pwd"))
		mini_pwd(env);
	else if (!ft_strcmp(args[0], "export"))
		handle_export(env, args);
	else if (!ft_strcmp(args[0], "unset"))
		process_unset(args, env);
	else if (!ft_strcmp(args[0], "env"))
		print_env_args(args);
	else if (!ft_strcmp(args[0], "exit"))
		mini_exit(args);
}
