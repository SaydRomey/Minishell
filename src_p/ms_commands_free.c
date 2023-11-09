/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:06:03 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:28:24 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Checks if any <fd_in>/<fd_out> file(s) descriptor -AND/OR- pipe end(s)
 * need(s) to be closed. If so, the close() function is called, and normally
 * assigns <0> to the previous opened FD.
*/
static void	ms_commands_node_free_closefd(t_commands **close_node_fd)
{
	if ((*close_node_fd)->pipe[RD] > DEFAULT && \
		(*close_node_fd)->pipe[RD] <= OPEN_MAX)
		(*close_node_fd)->pipe[RD] = \
		close((*close_node_fd)->pipe[RD]);
	if ((*close_node_fd)->pipe[WR] > DEFAULT && \
		(*close_node_fd)->pipe[WR] <= OPEN_MAX)
		(*close_node_fd)->pipe[WR] = \
		close((*close_node_fd)->pipe[WR]);
	if ((*close_node_fd)->fd_in[FD_STATUS] > DEFAULT && \
		(*close_node_fd)->fd_in[FD_STATUS] <= OPEN_MAX)
		(*close_node_fd)->fd_in[FD_STATUS] = \
		close((*close_node_fd)->fd_in[FD_STATUS]);
	if ((*close_node_fd)->fd_out[FD_STATUS] > DEFAULT && \
		(*close_node_fd)->fd_out[FD_STATUS] <= OPEN_MAX)
		(*close_node_fd)->fd_out[FD_STATUS] = \
		close((*close_node_fd)->fd_out[FD_STATUS]);
	return ;
}

/** -----
 * @brief Destroys a command table NODE, by freeing it's content, resetting
 * all it's values to <0>;<NULL>. Then the NODE itself is freed.
*/
static void	ms_commands_node_free(t_commands **node_to_free)
{
	if (node_to_free == NULL || \
		(*node_to_free) == NULL)
		return ;
	if ((*node_to_free)->cmd_path != NULL)
	{
		free((*node_to_free)->cmd_path);
		(*node_to_free)->cmd_path = NULL;
	}
	if ((*node_to_free)->cmd != NULL)
	{
		free((*node_to_free)->cmd);
		(*node_to_free)->cmd = NULL;
	}
	ms_commands_node_free_closefd(node_to_free);
	ft_bzero(*node_to_free, sizeof(*node_to_free));
	free(*node_to_free);
	(*node_to_free) = NULL;
	return ;
}

/** -----
 * @brief Iterates through the commands table, from START to END,
 * for each node to be properly destroyed.
*/
void	ms_commands_free(t_commands **head)
{
	t_commands	*current_node;
	t_commands	*node_to_remove;

	if (head == NULL || (*head) == NULL)
		return ;
	current_node = *head;
	while (current_node != NULL)
	{
		node_to_remove = current_node;
		current_node = current_node->next;
		ms_commands_node_free(&node_to_remove);
		node_to_remove = NULL;
	}
	(*head) = NULL;
	return ;
}
