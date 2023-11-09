/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:13:29 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 09:13:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
SIGINT (CTRL + C) handler for child process
displays a new prompt
rl_replace_line() clears the current line
rl_on_new_line() moves the cursor to the new line
rl_redisplay() displays the new prompt
*/
static void	child_sigint_handler(int signum)
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
sets SIGINT handler for child process
sigaction() sets the action for SIGINT to 'child_sigint_handler'
then sets SIGQUIT to default behaviour
*/
void	child_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = child_sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) == ERROR)
		exit_perror("Failed to reset SIGINT");
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGQUIT, &sa, NULL) == ERROR)
		exit_perror("Failed to reset SIGQUIT to default");
}
