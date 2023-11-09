/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:27:41 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/09 11:51:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ms_errors.h"
# include "macros.h"

# include <readline/readline.h> // readline
# include <readline/history.h> // add_history
# include <errno.h> // errno macros and error codes
# include <sys/wait.h> // wait, waitpid and macros to extract status values
# include <sys/types.h> // for data types (pid_t) used by wait, waitpid, etc.
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill

# include "minishell_p.h"
# include "minishell_c.h"

void	*minishell(t_minishell *data);

#endif
