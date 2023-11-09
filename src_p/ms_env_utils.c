/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:38:27 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:50:25 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Destroys the t_minishell environment and execution data.
*/
void	ms_env_free(void)
{
	t_minishell	*data_to_free;

	data_to_free = NULL;
	data_to_free = ms_env_pull();
	if (data_to_free == NULL)
		return ;
	if (data_to_free->commands_table != NULL)
		ms_commands_free(&data_to_free->commands_table);
	if (data_to_free->tokens != NULL)
		ms_lex_free(&data_to_free->tokens);
	ft_bzero((void *)data_to_free, sizeof(*data_to_free));
	free(data_to_free);
	data_to_free = NULL;
	return ;
}

/** -----
 * @brief Declares a pointer to a STATIC t_minishell STRUCT.
 * If the STRUCT is not yet existing, the necessary memory is allocated, 
 * values are zeroed using CALLOC.
*/ 
t_minishell	*ms_env_pull(void)
{
	static t_minishell	*data;

	if (data == NULL)
	{
		data = ft_alloc(CALLOC, 1, sizeof(*data));
		if (data == NULL)
			return (NULL);
	}
	return (data);
}
