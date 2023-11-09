/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:06:40 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 08:42:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
modifies current exit status
and updates the string version 'stratus'
(for '$?')
*/
void	set_exit_status(int exit_status)
{
	t_info	*info;

	info = call_info();
	info->status = exit_status;
	if (info->stratus != NULL)
	{
		free(info->stratus);
		info->stratus = NULL;
	}
	info->stratus = ft_itoa(info->status);
}

/*
get current exit status as an int
*/
int	get_exit_status(void)
{
	t_info	*info;

	info = call_info();
	return (info->status);
}

/*
returns a string with the current exit status
*/
char	*get_stratus(void)
{
	t_info	*info;

	info = call_info();
	if (!info->stratus || ft_strcmp(info->stratus, "") == SAME)
		return ("0");
	return (info->stratus);
}
