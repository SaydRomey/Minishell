/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:33:31 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 16:52:00 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
voids argc and argv, inits the t_minishell struct
inits the env list and
handles the 'SHLVL' variable
sets t_info's pointers to envp
initializes the prompt
*/
static void	init_data(t_minishell **data, char **envp)
{
	*data = ms_env_pull();
	if (!(*data))
		exit_error(ERR_DATA);
	set_envlst(init_env_list(envp));
	if (!get_envlist())
		exit_error(ERR_ENVLST);
	init_shlvl(get_envlist());
	set_envptr(envp);
	set_prompt();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;

	if (argc != 1)
	{
		ft_fprintf(FD_ERROR, "%s: %s: %s\n", EXEC_NAME, argv[1], ERR_ENOENT);
		return (EXIT_BAD_CMD);
	}
	init_data(&data, envp);
	minishell(data);
	return (SUCCESS);
}
