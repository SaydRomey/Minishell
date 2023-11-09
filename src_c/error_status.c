/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:39:37 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/02 15:02:00 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* str: ERR_MACRO */
void	error_status(char *str, char *err_macro, int status)
{
	ft_fprintf(FD_ERROR, "%s: %s\n", str, err_macro);
	set_exit_status(status);
}

/* Minishell: 'str': ERR_MACRO */
void	ms_error_status(char *str, char *err_macro, int status)
{
	ft_fprintf(FD_ERROR, EXEC_NAME);
	ft_fprintf(FD_ERROR, ": '%s': %s\n", str, err_macro);
	set_exit_status(status);
}

/* Minishell: cmd: 'arg': ERR_MACRO */
void	ms_cmd_error_status(char *cmd, char *str, char *err_macro, int status)
{
	ft_fprintf(FD_ERROR, EXEC_NAME);
	ft_fprintf(FD_ERROR, ": %s: '%s': %s\n", cmd, str, err_macro);
	set_exit_status(status);
}
