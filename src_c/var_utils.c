/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:39:18 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/01 21:42:18 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
creates a new variable instance
and sets its key, value and exported status
returns the variable
or NULL if malloc fails
*/
t_var	*new_var(char *key, char *value, int exported)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	if (!value)
		var->value = NULL;
	else
		var->value = ft_strdup(value);
	var->exported = exported;
	return (var);
}

/*
find variable by key
returns a pointer to the node containing the variable
or NULL if not found
*/
t_list	*find_var(t_list *env, char *key)
{
	t_list	*tmp;
	t_var	*var;

	tmp = env;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (ft_strcmp(var->key, key) == SAME)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
returns a copy of a t_var node
with a copy of its content
or NULL if malloc fails
*/
void	*dup_var(void *content)
{
	t_var	*var;
	t_var	*new;

	var = (t_var *)content;
	new = new_var(var->key, var->value, var->exported);
	return (new);
}

/*
frees a t_var node and its content
conditional free for key and value
*/
void	del_var(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var)
	{
		if (var->key)
			free(var->key);
		if (var->value)
			free(var->value);
		free(var);
	}
}

/*
to be valid, a variable name must:
start with a letter or an underscore
be followed by letters, numbers or underscores
*/
int	var_name_is_valid(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (FALSE);
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (FALSE);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
