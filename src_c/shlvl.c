/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:50:18 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 09:11:04 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
chacks for invalid SHLVL when setting up the environment
*/
static int	validate_shlvl(char *str)
{
	int	overflow;
	int	num;

	num = ft_atoi(str);
	overflow = flow_check(str);
	if (overflow == TRUE || num > SHLVL_LIMIT)
	{
		ft_fprintf(FD_ERROR, "Minishell: warning: \n");
		ft_fprintf(FD_ERROR, "shell level (%s) too high, resetting to 1\n", str);
		ft_strlcpy(str, "1", ft_strlen(str) + 1);
		return (FALSE);
	}
	if (num < 0)
	{
		ft_strlcpy(str, "0", ft_strlen(str) + 1);
		return (FALSE);
	}
	else if (num == SHLVL_LIMIT)
	{
		ft_strlcpy(str, "", ft_strlen(str) + 1);
		return (FALSE);
	}
	return (TRUE);
}

/*
adds '1' to the numerical string
edge-cases handled:
	if 'str' has non-numerical characters, SHLVL=1
	if 'str' is negative SHLVL=0
	if 'str' is at SHLVL_LIMIT, SHLVL=""
	if SHLVL is too high, SHLVL=1
*/
void	incr_shlvl(char *str)
{
	char	*new_str;

	if (ft_str_isdigit(str) == FALSE)
	{
		ft_strlcpy(str, "1", ft_strlen(str) + 1);
		return ;
	}
	if (validate_shlvl(str) == TRUE)
	{
		new_str = ft_itoa(ft_atoi(str) + 1);
		ft_strlcpy(str, new_str, ft_strlen(new_str) + 1);
		free(new_str);
	}
}

/*
handles SHLVL after 'init_env_list'
ither increments SHLVL by 1 if it was in 'envp'
or adds SHLVL=1 to the list if it wasn't.
handles various edge cases
*/
void	init_shlvl(t_list *env)
{
	char	*shlvl_value;

	shlvl_value = get_var_value(env, "SHLVL");
	if (shlvl_value)
		incr_shlvl(shlvl_value);
	else
		add_or_update_var(&env, "SHLVL", "1", TRUE);
}
