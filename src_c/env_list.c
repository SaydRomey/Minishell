/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:55:18 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/06 17:57:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
initialize the t_list 'env' from the 'envp' argument of main
returns the initialized env list
*/
t_list	*init_env_list(char **envp)
{
	t_list	*env;
	char	*equal_sign;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			key = envp[i];
			value = equal_sign + 1;
			add_or_update_var(&env, key, value, TRUE);
			*equal_sign = '=';
		}
		i++;
	}
	return (env);
}

/*
sets a pointer to 'env' in the static 'info' struct
*/
void	set_envlst(t_list *env)
{
	t_info	*info;

	info = call_info();
	info->envlst = env;
}

/*
to obtain the 'env' list from anywhere
*/
t_list	*get_envlist(void)
{
	t_info	*info;

	info = call_info();
	return (info->envlst);
}

/*
pointer to the main's envp argument
*/
void	set_envptr(char **envp)
{
	t_info	*info;

	info = call_info();
	info->envptr = envp;
}

/*
return pointer through 'info' struct to 'envp' from the main
*/
char	**get_envptr(void)
{
	t_info	*info;

	info = call_info();
	return (info->envptr);
}
