/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:42:01 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 18:49:10 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
iterates over the 'env' list and 
prints each variable if 'exported' is '1' and the value is not empty
*/
void	print_env(t_list *env)
{
	t_list	*tmp;
	t_var	*var;

	tmp = env;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (var->exported == TRUE && var->value != NULL)
			ft_printf("%s=%s\n", var->key, var->value);
		tmp = tmp->next;
	}
	set_exit_status(SUCCESS);
}

/*
Check if all args contain an '='
(used to print assignations following 'env')
** (but not to assign them) *
*/
static int	args_are_all_assignation(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '='))
		{
			error_status(args[i], ERR_BAD_CMD, 127);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/*
prints following assignations after calling 'print_env' but does not assign them
uses the 'args_are_all_assignations' function to check
*/
void	print_env_args(char **args)
{
	int	i;

	if (args_are_all_assignation(args) == FALSE)
		return ;
	print_env(get_envlist());
	i = 1;
	while (args[i])
	{
		ft_printf("%s\n", args[i]);
		i++;
	}
	set_exit_status(SUCCESS);
}
