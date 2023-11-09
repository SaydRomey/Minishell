/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:37:29 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 19:04:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Creates a new command table list based on tokens.
*/
static t_commands	*ms_commands_init(t_lex *tokens)
{
	t_commands	*commands;
	t_lex		*tmp;

	tmp = tokens;
	commands = ms_commands_new(NULL);
	while (tmp != NULL)
	{
		if (tmp->type == PIPE && \
			ft_strlen(tmp->token) == 1)
			ms_commands_addback(&commands, ms_commands_new(NULL));
		tmp = tmp->next;
	}
	return (commands);
}

/** -----
 * @brief Takes the information from the tokens linked list and places
 * references into the current command table NODE.
*/
static void	ms_commands_fill_node(t_commands *table, t_lex *tokens, size_t *x)
{
	if (tokens->type == TEXT)
		table->cmd[++(*x)] = tokens->token;
	else if (tokens->type >= REDIR__START && tokens->type <= REDIR__END)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_HDOC
			|| tokens->type == REDIR_HDOC_X)
		{
			if (table->fd_in[FD_STATUS] >= 0)
			{
				table->fd_in[FD_STATUS] = tokens->fd_status;
				table->fd_in[FD_TYPE] = tokens->type;
				table->infile = tokens->token;
			}
		}
		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_OUT_A)
		{
			table->fd_out[FD_STATUS] = tokens->fd_status;
			table->fd_out[FD_TYPE] = tokens->type;
			table->outfile = tokens->token;
		}
	}
	return ;
}

/** -----
 * @brief Checks if all TEXT typed tokens are ASSIGNATIONS.
 * If not, the list is dereferenced to point to the valid token.
*/
static void	ms_assignations_check(t_lex **list, t_lex *token)
{
	t_lex		*checked;
	static bool	assig;

	checked = token;
	while (checked != NULL && checked->type != PIPE)
	{
		if (checked->type >= REDIR__START && checked->type <= REDIR__END)
		{
			checked = checked->next;
			continue ;
		}
		if (ft_strchr(checked->token, '=') && ft_strcmp(checked->token, "="))
			assig = true;
		if (assig && \
			(!ft_strchr(checked->token, '=') || ft_strstr(checked->token, "=") \
			|| checked->token[0] == '='))
		{
			(*list) = checked;
			return ;
		}
		else if (checked->type == TEXT && assig == false)
			return ;
		checked = checked->next;
	}
	return ;
}

/** -----
 * @brief Iterates through the TOKENS linked list, updates each command
 * table NODES using the current valid token data/information (The commands
 * table are differentiated by '|' and '\0' characters.
*/
static void	ms_commands_fill(t_commands *data, t_lex *tokens)
{
	size_t	count;
	size_t	x;

	if (data == NULL || tokens == NULL)
		return ;
	while (tokens != NULL && data != NULL)
	{
		x = -1;
		ms_assignations_check(&tokens, tokens);
		count = ms_token_text_counter(tokens);
		data->cmd = ft_alloc(CALLOC, (count + 1), sizeof(*data->cmd));
		if (data->cmd == NULL)
			return ;
		while (tokens != NULL && tokens->type != PIPE)
		{
			ms_commands_fill_node(data, tokens, &x);
			tokens = tokens->next;
		}
		if (tokens != NULL && tokens->type == PIPE)
			tokens = tokens->next;
		data = data->next;
	}
	return ;
}

/** -----
 * @brief Creates a new commands table list, then builds the commands linked
 * list based on the parsed TOKENS linked list.
*/
void	ms_commands(t_minishell *data)
{
	if (data == NULL || data->tokens == NULL)
		return ;
	data->commands_table = ms_commands_init(data->tokens);
	if (data->commands_table == NULL)
		return ;
	ms_commands_fill(data->commands_table, data->tokens);
	return ;
}
