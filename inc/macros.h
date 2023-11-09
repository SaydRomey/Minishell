/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:08:38 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 16:45:08 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define EXEC_NAME			"Minishell"
# define SNEAKY_MESSAGE		"very_sneaky"

# define PRMPT_PREFIX		"sneaky_"
# define PRMPT_DFLT			"individual"
# define PRMPT_SUFFIX		" -> "

# define PRMPT_CLR_DFLT		2
# define SHLVL_LIMIT		999
# define ECHO_FLAGS			"nr"

/* ************************************************************************** */

# define DEFAULT_PATH		"PATH"
# define HEREDOC_TMP_PATH	"/tmp/"
# define HEREDOC_EXT		".heredoc"
# define HEREDOC_PROMPT		".heredoc> "
# define DEV_NULL			"/dev/null"
# define CHILD_PROCESS		0

# define EXIT_CUE			"exit"
# define FD_PERMISSION		0644

# define REFERENCE			0
# define DEFAULT			0
# define IGNORED_PARAM		0

# define RD					0
# define WR					1
# define IN					0
# define OUT				1

# define FD_STATUS			0
# define FD_TYPE			1

/* ****************************** TOKEN TYPES ******************************* */

# define TEXT				102
# define TEXT_X				103
# define WHITESPACE			104

# define COMMAND			105
# define META_C				106

# define S_QUOTE			201
# define D_QUOTE			202
# define UNCLOSED_QUOTE 	203
# define FLAG				206
# define PIPE				207

/** -----
 * @brief Redirection values MIN limit.
*/
# define REDIR__START		300
/*token: <*/
# define REDIR_IN			310
/*token: << && token->next == IDENTIFIER*/
# define REDIR_HDOC			320
/*token: << && token->next = 'IDENTIFIER'*/
# define REDIR_HDOC_X		321
/*token: >*/
# define REDIR_OUT			340
/*token: >>*/
# define REDIR_OUT_A		341
/*token: Any repeated <REDIR_TOKEN> (ex: <<< OR >>>)*/
# define REDIR_INVALID		398
/** -----
 * @brief Redirection values MAX limit.
*/
# define REDIR__END			399

/*Any type that does not meet the requirements of a valid token*/
# define PARSE_ERROR		666
# define REDIR_SIGINT		OPEN_MAX + 2

#endif
