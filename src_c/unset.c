/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:30:24 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 09:16:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
handles the removal of a variable
updates the environment list
*/
void	unset_var(t_list **env, char *key)
{
	t_list	*found;

	found = find_var(*env, key);
	if (found)
		ft_lstremoveone(env, found, del_var);
	set_envlst(*env);
}

/*
handles the 'unset' command
*/
void	process_unset(char **args, t_list *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_var(&env, args[i]);
		i++;
	}
}
