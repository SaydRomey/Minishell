/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:57:45 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 09:02:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
restores variables from envp to the env list
if they aren't already present
*/
static void	restore_missing_vars(t_list **env, char **envp)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = envp[i];
			value = equal_sign + 1;
			if (!find_var(*env, key))
			{
				add_or_update_var(env, key, value, TRUE);
			}
			*equal_sign = '=';
		}
		i++;
	}
}

/*
restores the initial value of a variable,
or if a variable with given key exists,
updates its value with its initial value
otherwise, if it was not in the original envp,
removes it from the list
*/
static void	reset_var(t_list **env, char *key)
{
	char	*value;

	value = getenv(key);
	if (value == NULL)
		unset_var(env, key);
	else
		add_or_update_var(env, key, value, TRUE);
}

/*
re-initializes the env list with the original envp
if SHLVL is in envp, increments it by 1
(we are in a subshell)
*/
static void	re_init_env(t_list **env, char **envp)
{
	t_list	*current;

	current = *env;
	while (current)
	{
		reset_var(env, ((t_var *)current->content)->key);
		current = current->next;
	}
	restore_missing_vars(env, envp);
	init_shlvl(*env);
}

/*
resets environment variables to their original values
or removes them if they were not in the original envp
usage: reset [var1] [var2] ... [varN]
** if "env" is in any args, all the list is reset *
** if the list is completely empty, any args will reset the list *
*/
void	reset_env(t_list **env, char **args, char **envp)
{
	int	i;

	if (!(*env))
	{
		set_envlst(init_env_list(get_envptr()));
		if (!get_envlist())
			return ;
		init_shlvl(get_envlist());
	}
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "env") == SAME)
		{
			re_init_env(env, envp);
			return ;
		}
		i++;
	}
	i = 1;
	while (args[i])
	{
		reset_var(env, args[i]);
		i++;
	}
}
