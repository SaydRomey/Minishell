/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:11:27 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 18:22:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
returns 'exported' value of t_var node
*/
static int	is_exported(t_list *env)
{
	t_var	*var;

	var = (t_var *)env->content;
	if (var->exported)
		return (TRUE);
	return (FALSE);
}

/*
handle the assignation of variables
all args must be assignations (already verified in parsing)
validates the name of the variable
*/
void	assign_var(t_list *env, char **args)
{
	int		i;
	t_list	*existing_var;
	char	**key_value;

	i = 0;
	set_exit_status(SUCCESS);
	while (args[i])
	{
		key_value = ft_split(args[i], '=');
		if (key_value && key_value[0] && key_value[1])
		{
			if (var_name_is_valid(key_value[0]))
			{
				existing_var = find_var(env, key_value[0]);
				if (existing_var && is_exported(existing_var))
					add_or_update_var(&env, key_value[0], key_value[1], TRUE);
				else
					add_or_update_var(&env, key_value[0], key_value[1], FALSE);
			}
			else
				error_status(args[i], ERR_BAD_CMD, 127);
		}
		free_split(key_value);
		i++;
	}
}
