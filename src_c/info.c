/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wip_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:56:57 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/23 14:51:12 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
on first call: allocates t_info struct and returns it
on subsequent calls: returns the same struct
*/
t_info	*call_info(void)
{
	static t_info	*info;

	if (info == NULL)
	{
		info = ft_calloc(1, sizeof(*info));
		if (info == NULL)
			return (NULL);
	}
	return (info);
}

/*
frees all allocated memory in the t_info struct
*/
void	free_info(void)
{
	t_info	*info;

	info = call_info();
	if (info->envlst)
		ft_lstclear(&info->envlst, del_var);
	if (info->stratus)
		free(info->stratus);
	if (info->prompt)
		free(info->prompt);
	if (info->envchild)
		free_split(info->envchild);
	free(info);
}

/*
used to free all allocated memory before exiting the program
free_info() is for the t_info struct
ms_env_free() is for the t_minishell struct
*/
void	destroy_all(void)
{
	free_info();
	ms_env_free();
}
