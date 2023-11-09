/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:24:28 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 16:46:25 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERRORS_H
# define MS_ERRORS_H

/* The process has not exited correctly (interruption, etc.) */
# define WRONG_IFEXIT 0

/* Parse error exit status */
# define EXIT_ERRNO_PARSE 258

/* Not correctly exited process exit status */
# define EXIT_ERRNO_WRONG_IFEXIT 130

/* Command/File/Dir not found */
# define EXIT_BAD_CMD 127

/* ************************************************************************** */
/* ***************************** ERROR MESSAGES ***************************** */

# define ERROR_PARSE_NEAR		"Parse error or Syntax error near"
# define WRONG_INFILE			"No such infile or directory"
# define WRONG_OUTFILE			"No such outfile or \
								directory, or Permission denied"
# define ERROR_DUP_TO			"Duplicating to (dup2) file descriptor"
# define ERROR_DUP				"Duplicating (dup) file descriptor"
# define ERROR_FORK_MASTER_EXEC	"Forking master execution process"
# define ERROR_FORK_EXEC 		"Forking command execution process"
# define ERROR_FORK_HEREDOC		"Forking heredoc process"
# define ERROR_PIPE_CREATION	"Initializing pipeline"
# define ERROR_UNLINK_HDOC		"Deleting <.heredoc> file"
# define ERROR_EXECVE			"Command not found or Permission denied"

# define ERR_DATA				"Failed to allocate memory for data struct"
# define ERR_ENVLST				"Failed to initialize environment"
# define ERR_NOPATH				"Failed to get path list (try 'reset PATH')\n"
# define ERR_BAD_CMD			"command not found"
# define ERR_INV_ID				"not a valid identifier"
# define ERR_ENOENT				"No such file or directory"
# define ERR_OLDPWD				"OLDPWD not set"
# define ERR_NOHOME				"HOME not set"
# define ERR_NUM_ARG			"numeric argument required"
# define ERR_NO_PERM			"Permission denied"

#endif
