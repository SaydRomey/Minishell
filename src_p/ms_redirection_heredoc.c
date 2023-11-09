/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:45:54 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:09:46 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Determines if the HEREDOC process should end.
*/
bool	ms_end_heredoc_process(char *rl, char *delimiter)
{
	if (rl == NULL || ft_strcmp(rl, delimiter) == 0)
	{
		if (rl != NULL)
		{
			free(rl);
			rl = NULL;
			return (true);
		}
	}
	return (false);
}

/** -----
 * @brief Analyzes the type of HEREDOC and input, then disptaches it to
 * the text processing action.
*/
static void	ms_heredoc_input(char **rl, char *delimit, int fd_type, int fd_hdoc)
{
	char	*hdoc_prompt;

	hdoc_prompt = NULL;
	hdoc_prompt = ft_strjoin(delimit, HEREDOC_PROMPT);
	while (LOOP)
	{
		signal(SIGINT, SIG_DFL);
		*rl = readline(hdoc_prompt);
		if (ms_end_heredoc_process(*rl, delimit) == true || *rl == NULL)
			break ;
		if (fd_type == REDIR_HDOC)
			ms_heredoc_expansion(rl);
		ft_putendl_fd(*rl, fd_hdoc);
		free(*rl);
		*rl = NULL;
	}
	free(hdoc_prompt);
	hdoc_prompt = NULL;
	return ;
}

/** -----
 * @brief Process that takes the input of the user and writes to the HEREDOC.
*/
static int	ms_input_to_heredoc(char *hdoc_name, char *delimiter, int fd_type)
{
	char	*hdoc;
	int		fd_hdoc;
	char	*rl;

	hdoc = ft_strjoin(HEREDOC_TMP_PATH, hdoc_name);
	fd_hdoc = open(hdoc, CREATE | READ_WRITE | TRUNCATE, FD_PERMISSION);
	if (fd_hdoc < 0)
	{
		perror("Opening heredoc.");
		return (fd_hdoc);
	}
	rl = NULL;
	ms_heredoc_input(&rl, delimiter, fd_type, fd_hdoc);
	close(fd_hdoc);
	free(hdoc);
	hdoc = NULL;
	return (fd_hdoc);
}

/** -----
 * @brief Manages the process of the HEREDOC.
*/
static int	ms_heredoc(char *hdoc_name, char *delimiter, int fd_type)
{
	pid_t	hdoc_pid;
	int		hdoc_fd_status;

	hdoc_fd_status = -1;
	signal(SIGINT, SIG_IGN);
	hdoc_pid = fork();
	if (hdoc_pid < CHILD_PROCESS)
	{
		error_status(EXEC_NAME, ERROR_FORK_HEREDOC, errno);
		return (hdoc_fd_status);
	}
	if (hdoc_pid == CHILD_PROCESS)
	{
		hdoc_fd_status = ms_input_to_heredoc(hdoc_name, delimiter, fd_type);
		exit(hdoc_fd_status);
	}
	else
		waitpid(hdoc_pid, &hdoc_fd_status, 0);
	return (hdoc_fd_status);
}

/** -----
 * @brief Handles the creation and execution of an HEREDOC process.
*/
void	ms_heredoc_init(t_lex *token, char *fd_name, int *fd_no, int fd_type)
{
	char	*heredoc_name;

	heredoc_name = NULL;
	heredoc_name = ms_get_heredoc_name(fd_name);
	(*fd_no) = ms_heredoc(heredoc_name, fd_name, fd_type);
	if (WIFEXITED(*fd_no))
		(*fd_no) = WEXITSTATUS(*fd_no);
	else if (WIFEXITED(*fd_no) == 0)
	{
		ft_printf("\n");
		(*fd_no) = REDIR_SIGINT;
		free(token->token);
		token->token = ft_strjoin(HEREDOC_TMP_PATH, heredoc_name);
		free(heredoc_name);
		return ;
	}
	if (*fd_no > 0)
	{
		free(token->token);
		token->token = ft_strjoin(HEREDOC_TMP_PATH, heredoc_name);
		free(heredoc_name);
	}
	return ;
}
