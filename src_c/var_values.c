/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:13:33 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 15:08:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
returns the value of a variable
or NULL if not found
*/
char	*get_var_value(t_list *env, char *key)
{
	t_list	*node;
	t_var	*var;

	node = find_var(env, key);
	if (node)
	{
		var = (t_var *)node->content;
		return (var->value);
	}
	return (NULL);
}

/*
if a variable with given key exists, updates its value
otherwise adds a new variable to the list
if malloc fails, does nothing **?
*/
void	add_or_update_var(t_list **env, char *key, char *value, int exported)
{
	t_list	*found;
	t_var	*var;
	t_list	*new;

	found = find_var(*env, key);
	if (found)
	{
		var = (t_var *)found->content;
		free(var->value);
		var->value = ft_strdup(value);
		var->exported = exported;
	}
	else
	{
		var = new_var(key, value, exported);
		if (!var)
			return ;
		new = ft_lstnew(var);
		ft_lstadd_back(env, new);
	}
}
