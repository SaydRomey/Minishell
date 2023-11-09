/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:57:09 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/21 01:57:28 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
tmp to see shell vars
(assigned variables that are not exported yet)
*/
void	display_shell_vars(t_list *env)
{
	t_list	*tmp;
	t_var	*var;

	tmp = env;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (var->exported == FALSE)
			ft_printf("%s=%s\n", var->key, var->value);
		tmp = tmp->next;
	}
}
