/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_p.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:06:03 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 15:53:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_P_H
# define MINISHELL_P_H

# include "minishell.h"

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

/** -----
 * @param cmd_path Absolute path of the actual command (if existent)
 * @param cmd cmd[0] == command itself / cmd[1++] == argument
 * @param infile Name of INFILE (if mentionned in the readline input)
 * @param outfile Name of OUTFILE (if mentionned in the readline input)
 * @param pipe Pipe[2] for the actual command process. To communicate with
 * previous, and next command(s) process(es).
 * @param fd_in fd_in[0] == fd_status / fd_in[1] == fd_type (HDOC, etc.)
 * @param fd_out fd_out[0] == fd_status / fd_out[1] == fd_type
 * (APPEND, TRUNC, etc.)
 * @param pid The actual command's process identification.
 * @param next Pointer to the next command table node.
 * @param previous Pointer to the previous command table node.
*/
typedef struct s_commands
{
	char				*cmd_path;
	char				**cmd;
	char				*infile;
	char				*outfile;
	int					pipe[2];
	int					fd_in[2];
	int					fd_out[2];
	pid_t				pid;
	struct s_commands	*next;
	struct s_commands	*previous;
}	t_commands;

/** -----
 * @param token Characters string that has been extracted from read line.
 * @param type Type of token (<PIPE>; <TEXT>; <REDIR>; etc.)
 * @param fd_status If the token is the name of a file, the redirection
 * validation result is stored here. It is then used in the commands table
 * filling process. If -1; Means that to file was not openable/creatable.
 * @param next Pointer to the next token node
 * @param previous Pointer to the previous token node
*/
typedef struct s_lex
{
	char			*token;
	int				type;
	int				fd_status;
	struct s_lex	*next;
	struct s_lex	*previous;
}	t_lex;

/** -----
 * @param tokens Pointer towards tokens linked list built from read line input
 * @param commands_table Linked list with parsed tokens into command tables
 * @param last_exit_status TBD
*/
typedef struct s_minishell
{
	t_lex		*tokens;
	t_commands	*commands_table;
}	t_minishell;

/* ************************************************************************** */
/*                              LEXER LIST UTILS                              */
/* ************************************************************************** */
/* ms_lexer_list_utils.c */

t_lex		*ms_lex_new(char *token, int type);
t_lex		*ms_lex_last(t_lex *first);
void		ms_lex_addback(t_lex **head, t_lex *new);
size_t		ms_lex_size(t_lex *list);

/* ******************************* LIST CLEAN ******************************* */
/* ms_lexer_clean.c */

void		ms_lex_node_detach(t_lex **list, t_lex *remove);
void		ms_lex_node_remove(t_lex **list, t_lex **remove);
void		ms_lex_toremove(t_lex **list, t_lex **toremove);
void		ms_lex_clean(t_lex **list);

/* ******************************* LIST FREE ******************************** */
/* ms_lexer_list_free.c */

void		*ms_lex_free_node(t_lex **node);
void		ms_lex_free(t_lex **list);

/* ************************************************************************** */
/*                                   CHECKS                                   */
/* ************************************************************************** */
/* ****************************** TOKEN CHECKS ****************************** */
/* ms_token_checks.c */

bool		ms_ismeta(int c);
bool		ms_isquote(int c);
bool		ms_isflag(int c);

/* ************************************************************************** */
/*                               TOKENIZATION                                 */
/* ************************************************************************** */
/* ****************************** TOKEN CREATE ****************************** */
/* ms_token_create.c */

void		ms_token_quote_create(t_lex **lexer, char **tmp, size_t *i);
void		ms_token_meta_create(t_lex **lexer, char **tmp, size_t *i);
void		ms_token_flag_create(t_lex **lexer, char **tmp, size_t *i);
void		ms_token_text_create(t_lex **lexer, char **tmp, size_t *i);
void		ms_token_whitespace_create(t_lex **lexer, char **tmp, size_t *i);

/* ****************************** TOKEN CLEAN ******************************* */
/* ms_token_clean-2 */

void		ms_token_quote_clean(t_lex *list);
void		ms_token_meta_clean(t_lex *list);
void		ms_token_text_clean(t_lex *list);
void		ms_token_flag_clean(t_lex *list);

/* ms_token_clean-1.c */

void		*ms_token_clean(t_lex *list);

/* ms_lexer.c */

void		ms_lex_arrange(t_lex **list);
void		ms_pre_lexer(t_minishell **data, char *input);

/* ******************************* TOKEN TYPE ******************************* */
/* ms_token_types_utils.c */

void		ms_token_text_type_specifier(t_lex *list);
void		ms_token_quote_type_selecter(t_lex *list);
void		ms_token_redir_type_selecter(t_lex *list);

/* ms_token_types.c */

void		ms_lex_type_specifier(t_lex **lexer);
void		ms_lex_retype(t_lex **lexer);

/* ************************************************************************** */
/*                            MISCELLANEOUS UTILS                             */
/* ************************************************************************** */
/* ms_skip_utils.c */

void		ms_skip_quote(char *s, size_t *i);
void		ms_close_dollarsign(char *s, size_t *i);
void		ms_skip_expandable_content(char *content, size_t *i);
void		ms_skip_text(char *s, size_t *i);
void		ms_skip_whitespaces(char **tmp, size_t	*i);

/* ms_count_utils.c */

size_t		ms_count_expandable_dollar(char *s_to_expand);
size_t		ms_strlen_exclude_expandables(char *s_to_expand);
size_t		ms_token_text_counter(t_lex *tokens);

/* ************************************************************************** */
/*                                 EXPANSION                                  */
/* ************************************************************************** */
/* ms_expand.c */

bool		ms_is_expandable_content(char *content);
char		*ms_expand(char *str_to_expand);

/* ms_expand_utils.c */

void		ms_skip_multi_dollar(char *str_to_expand, size_t *i);
bool		ms_is_valid_expandable(char *possible_key);
char		**ms_store_expandable_key(char *str_to_expand, char **variables);
char		*ms_find_corresponding_value(char *expandable_key);

/* ms_expansion.c */

void		ms_lex_expansion_process(t_lex **head);

/* ************************************************************************** */
/*                              COMMAND TABLES                                */
/* ************************************************************************** */
/* ms_commands.c */

void		ms_commands(t_minishell *data);

/* ms_commands_utils.c */

t_commands	*ms_commands_new(char *content);
t_commands	*ms_commands_last(t_commands *first);
void		ms_commands_addback(t_commands **head, t_commands *new);

/* ms_commands_free.c */

void		ms_commands_free(t_commands **head);

/* ************************************************************************** */
/*                             ENVIRONMENT UTILS                              */
/* ************************************************************************** */
/* ms_env_utils.c */

t_minishell	*ms_env_pull(void);
void		ms_env_free(void);

/* ************************************************************************** */
/*                                  ERRORS                                    */
/* ************************************************************************** */
/* ms_errors.c */

bool		ms_parse_error(t_lex *tokens);

/* ************************************************************************** */
/*                                REDIRECTION                                 */
/* ************************************************************************** */
/* ms_execution_redirection_io_fd.c */

void		ms_redirect_io_fd(t_commands *cmd);

/* ms_execution_redirection_io_utils.c */

void		ms_close_previous_remaining_fd(t_commands *cmd);
void		ms_close_next_remaining_fd(t_commands *cmd);
void		ms_close_remaining_fd(t_commands *cmd);

/* ms_execution_redirection_io.c */

int			ms_redir_input_from_file(const char *filename, int type);
int			ms_redir_output_to_file(const char *filename, int type);
int			ms_redirect_io(t_commands *cmd);

/* ms_redirections_checks.c */

int			ms_open_type(t_lex *token, char *fd_name, int fd_type, bool check);
void		ms_redir_validation(t_lex *token);

/* ms_redirection_heredoc_utils.c */

void		ms_close_heredoc(t_lex *token);
char		*ms_get_heredoc_name(char *fd_name);
void		ms_heredoc_expansion(char **rl);

/* ms_redirection_heredoc.c */

bool		ms_end_heredoc_process(char *rl, char *delimiter);
void		ms_heredoc_init(t_lex *token, char *fd_name, \
							int *fd_no, int fd_type);

/* ms_execution_redirection_io_single.c */

bool		ms_exec_is_single(t_commands *cmd);

/* ************************************************************************** */
/*                                 EXECUTION                                  */
/* ************************************************************************** */
/* ms_execution.c */

void		ms_execution(t_commands *cmd);

/* ms_execution_utils.c */

void		ms_dup(int to_dup, int *store);
void		ms_dup2(int todup, int fd);
void		ms_execve(char *command, char **cmd_param, char **envp);

/* ms_execution_pipeline.c */

void		ms_pipe_build(t_commands *cmd);

#endif
