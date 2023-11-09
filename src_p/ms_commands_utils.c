/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:16:05 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 11:42:07 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Creates a new command table NODE.
*/
t_commands	*ms_commands_new(char *content)
{
	t_commands	*new;

	new = NULL;
	new = ft_alloc(CALLOC, 1, sizeof(*new));
	if (new == NULL)
		return (new);
	new->cmd_path = content;
	new->fd_in[FD_STATUS] = OPEN_MAX + 1;
	new->fd_in[FD_TYPE] = INT_MIN;
	new->fd_out[FD_STATUS] = OPEN_MAX + 1;
	new->fd_out[FD_TYPE] = INT_MIN;
	return (new);
}

/** -----
 * @brief Iterates through the commands table linked list and finds the last
 * command table NODE.
*/
t_commands	*ms_commands_last(t_commands *first)
{
	t_commands	*last_node_finder;

	if (first == NULL)
		return (NULL);
	last_node_finder = first;
	while (last_node_finder->next != NULL)
		last_node_finder = last_node_finder->next;
	return (last_node_finder);
}

/** -----
 * @brief Adds a new command table NODE at the end of the linked list.
*/
void	ms_commands_addback(t_commands **head, t_commands *new)
{
	t_commands	*last_command_table_node;

	last_command_table_node = NULL;
	if (head == NULL || \
		new == NULL)
		return ;
	if (*head == NULL)
	{
		(*head) = new;
		return ;
	}
	last_command_table_node = ms_commands_last(*head);
	last_command_table_node->next = new;
	new->previous = last_command_table_node;
	return ;
}
