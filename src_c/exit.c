/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:24:39 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/01 21:14:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
exiting with 'CTRL+D'
*/
void	process_exit(char *input)
{
	if (input)
		free(input);
	destroy_all();
	ft_putendl_fd("exit", FD_OUTPUT);
	exit(SUCCESS);
}

/*
exiting with 'exit [n]'
handles non-numeric arguments
*/
void	mini_exit(char **args)
{
	int		exit_status;

	exit_status = 0;
	ft_putendl_fd(EXIT_CUE, FD_OUTPUT);
	if (args[1])
	{
		if (ft_isdigit(args[1][0]) == FALSE)
		{
			ms_cmd_error_status(EXIT_CUE, args[1], ERR_NUM_ARG, 255);
			exit_status = 255;
		}
		else
			exit_status = ft_atoi(args[1]);
	}
	destroy_all();
	exit(exit_status);
}
