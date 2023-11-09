/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:48:52 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 08:48:16 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
updates the 'exported' flag for the given key
if the variable doesn't exist, does nothing
*/
static void	export_var(t_list **env, char *key)
{
	t_list	*found;
	t_var	*var;

	found = find_var(*env, key);
	if (found)
	{
		var = (t_var *)found->content;
		var->exported = TRUE;
	}
}

/*
if the argument is a valid variable name,
adds it to the environment with the given value
*/
static void	export_and_assign(t_list **env, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	*equal_sign = '\0';
	if (var_name_is_valid(arg))
		add_or_update_var(env, arg, equal_sign + 1, TRUE);
	else
	{
		*equal_sign = '=';
		ms_error_status(arg, ERR_INV_ID, 1);
	}
}

/*
if the argument is a valid variable name,
if the variable exists, sets the 'exported' flag to TRUE
if the variable doesn't exist,
adds it to the environment with no value
*/
static void	export_by_key(t_list **env, char *arg)
{
	if (var_name_is_valid(arg))
	{
		if (find_var(*env, arg) == NULL)
			add_or_update_var(env, arg, NULL, TRUE);
		else
			export_var(env, arg);
	}
	else
		ms_error_status(arg, ERR_INV_ID, 1);
}

/*
export [name[=value] ...]

names refer to shell variables

if no names are supplied, a list of names of all exported variables is displayed

if a variable name is followed by '=value',
	the value of the variable is set to 'value'

** return status is '0' unless an invalid option is supplied
	or one of the names is not a valid shell variable name *
*/
void	handle_export(t_list *env, char **args)
{
	int	i;

	set_exit_status(SUCCESS);
	if (!args[1])
	{
		print_export(env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			export_and_assign(&env, args[i]);
		else
			export_by_key(&env, args[i]);
		i++;
	}
}
