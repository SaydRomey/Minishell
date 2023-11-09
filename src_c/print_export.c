/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:41:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 11:38:18 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
returns a copy of the list
** deep copy * (isolated from the original list)
returns NULL if the content duplication fails or if the list is empty
*/
t_list	*copy_var_list(t_list *lst)
{
	t_list	*copied_lst;

	copied_lst = ft_lstcpy(lst, dup_var, del_var);
	return (copied_lst);
}

/*
compare t_var nodes by key
**(used by ft_lstsort)*
*/
static int	cmp_by_key(t_list *lst_a, t_list *lst_b)
{
	t_var	*va;
	t_var	*vb;

	va = lst_a->content;
	vb = lst_b->content;
	return (ft_strcmp(va->key, vb->key));
}

/*
creates a copy of the 'env' list, sorts it by key,
then iterates over the sorted list
and prints each variable,
if 'exported' is set to '1' 
(with the required 'bash-like' formatting)
*/
void	print_export(t_list *env)
{
	t_list	*copy;
	t_list	*tmp;
	t_var	*var;

	copy = copy_var_list(env);
	if (!copy)
		return ;
	copy = ft_lstsort(copy, cmp_by_key);
	tmp = copy;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (var->exported == TRUE)
		{
			if (var->value && *(var->value) != '\0')
				ft_printf("declare -x %s=\"%s\"\n", var->key, var->value);
			else if (var->value && *(var->value) == '\0')
				ft_printf("declare -x %s=\"\"\n", var->key);
			else
				ft_printf("declare -x %s\n", var->key);
		}
		tmp = tmp->next;
	}
	ft_lstclear(&copy, del_var);
	set_exit_status(SUCCESS);
}
