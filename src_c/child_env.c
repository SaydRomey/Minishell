/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:03:40 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 08:34:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
returns an array of strings containing all exported variables in t_list 'env'
(to be used as envp in execve)
** must be freed *
*/
static char	**child_env(t_list *env)
{
	int		i;
	int		size;
	char	**env_arr;
	t_var	*var;

	size = ft_lstsize(env);
	env_arr = malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		var = (t_var *)env->content;
		if (var->exported == TRUE)
		{
			env_arr[i] = ft_strjoin_with(var->key, var->value, "=");
			i++;
		}
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

/*
creates the envp for execve with info from 'env' t_list
*/
char	**get_child_env(void)
{
	t_info	*info;

	info = call_info();
	if (info->envchild != NULL)
	{
		free(info->envchild);
		info->envchild = NULL;
	}
	info->envchild = child_env(get_envlist());
	return (info->envchild);
}
