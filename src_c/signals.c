/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:07:37 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 09:13:48 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
SIGINT (CTRL + C) handler for parent process
displays a new prompt
rl_replace_line() clears the current line
rl_on_new_line() moves the cursor to the new line
rl_redisplay() displays the new prompt
*/
static void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
sets SIGINT handler for parent process
sigemptyset() initializes the signal set given by sa_mask
sa_flags is set to SA_RESTART to restart interrupted system calls
sigaction() sets the action for SIGINT to 'handle_sigint'
*/
static void	set_sigint_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		exit_perror("Failed to set SIGINT handler");
}

/*
ignores SIGQUIT (CTRL + \)
sigaction() sets the action for SIGQUIT to SIG_IGN (ignore)
*/
static void	ignore_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		exit_perror("Failed to ignore SIGQUIT");
}

/*
modifies the behaviour of SIGINT and SIGQUIT
*/
void	init_signals(void)
{
	set_sigint_handler();
	ignore_sigquit();
}
