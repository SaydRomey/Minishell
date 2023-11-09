/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 22:30:11 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/02 14:01:45 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
returns TRUE if all flags are valid
(if each char in 'arg' is in 'valid_flags')
*/
static int	is_valid_flag(const char *arg, const char *valid_flags)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_strchr(valid_flags, arg[i]) == NULL)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
iterates the args, sets the flags accordingly
returns the index after the last processed (valid) flag
*/
static int	process_flags(char **args, t_echo_flags *flags)
{
	int	i;

	i = 1;
	while (args[i] && args[i][0] == '-' && is_valid_flag(args[i], ECHO_FLAGS))
	{
		if (ft_strchr(args[i], 'n'))
			flags->new_line = FALSE;
		if (ft_strchr(args[i], 'r'))
			flags->rainbow = TRUE;
		i++;
	}
	return (i);
}

/*
handles 'n' flag (no newline)
and special 'r' flag (rainbow)
*/
void	mini_echo(char **args)
{
	int				i;
	t_echo_flags	flags;

	flags.new_line = TRUE;
	flags.rainbow = FALSE;
	i = process_flags(args, &flags);
	while (args[i] != NULL)
	{
		if (flags.rainbow)
			ft_strainbow(args[i], FALSE);
		else
			ft_printf("%s", args[i]);
		if (*args[i] && args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (flags.new_line)
		ft_printf("\n");
	set_exit_status(SUCCESS);
}
