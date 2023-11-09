/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:23:03 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 08:58:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
use getcwd() to fetch the current working directory and print it
*/
static void	failsafe_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return ;
	}
	ft_printf("%s\n", cwd);
	set_exit_status(SUCCESS);
}

/*
pwd from 'env' list
**(if PWD is unset, uses 'getcwd')*
*/
void	mini_pwd(t_list *env)
{
	t_list	*pwd_node;
	t_var	*pwd_var;

	pwd_node = find_var(env, "PWD");
	if (!pwd_node)
	{
		failsafe_pwd();
		return ;
	}
	pwd_var = (t_var *)pwd_node->content;
	ft_printf("%s\n", pwd_var->value);
	set_exit_status(SUCCESS);
}
