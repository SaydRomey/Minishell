/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:09:39 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 18:12:01 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
'shellv' (to see which non-exported variables exist)
'reset' (restore variable.s with getenv)
*/
int	is_secret_builtin(char *cmd)
{
	char	*secret[3];
	int		i;

	i = 0;
	secret[0] = "shellv";
	secret[1] = "reset";
	secret[2] = NULL;
	while (secret[i])
	{
		if (ft_strcmp(cmd, secret[i]) == SAME)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
dispatches to the right builtin function
*/
static int	is_builtin(char *cmd)
{
	char	*builtins[8];
	int		i;

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == SAME)
			return (TRUE);
		i++;
	}
	if (ft_strchr(cmd, '=') != NULL && ft_strstr(cmd, "=") == NULL)
		return (TRUE);
	return (FALSE);
}

/*
checks the string for
'is_builtin' and 'is_secret_builtin'
*/
int	is_valid_builtin(char *cmd)
{
	if (is_builtin(cmd) == TRUE || is_secret_builtin(cmd) == TRUE)
		return (TRUE);
	return (FALSE);
}
