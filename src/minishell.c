/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:05:52 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 18:49:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
updates the data struct with the new input
*/
static void	update_data(t_minishell **data, char *input)
{
	if ((*data)->tokens != NULL)
		ms_lex_free(&(*data)->tokens);
	if ((*data)->commands_table != NULL)
		ms_commands_free(&(*data)->commands_table);
	ms_pre_lexer(data, input);
	ms_lex_arrange(&(*data)->tokens);
}

static int	has_command(t_minishell *data)
{
	t_lex	*tmp;

	tmp = data->tokens;
	while (tmp != NULL)
	{
		if (tmp->type == TEXT)
			return (TRUE);
		tmp = tmp->next;
		if (tmp == NULL)
		{
			tmp = data->tokens;
			while (tmp != NULL)
			{
				if (tmp->fd_status < 0 || tmp->fd_status > OPEN_MAX)
				{
					ms_error_status(tmp->token, WRONG_INFILE, 1);
					return (FALSE);
				}
				tmp = tmp->next;
			}
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	parse(char *input, t_minishell *data)
{
	update_data(&data, input);
	if (ms_parse_error(data->tokens) == FALSE)
	{
		ms_redir_validation(data->tokens);
		if (get_exit_status() == REDIR_SIGINT)
		{
			ms_close_heredoc(data->tokens);
			ms_lex_free(&data->tokens);
			set_exit_status(1);
			return (FAILURE);
		}
		if (has_command(data) == TRUE)
			return (SUCCESS);
	}
	return (FAILURE);
}

void	*minishell(t_minishell *data)
{
	char	*input;

	while (LOOP)
	{
		init_signals();
		colorized_prmpt();
		input = readline(get_prompt());
		ft_printf(RESET);
		if (parse(input, data) == SUCCESS)
		{
			ms_commands(data);
			ms_execution(data->commands_table);
		}
		if (input && *input)
			add_history(input);
		if (!input)
			process_exit(input);
		ms_close_heredoc(data->tokens);
		free(input);
	}
}
