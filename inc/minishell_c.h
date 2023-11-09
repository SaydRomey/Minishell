/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_c.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:48:19 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/08 11:43:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_C_H
# define MINISHELL_C_H

# include "minishell.h"

/* structs */

// environment variables (nodes of a t_list)
typedef struct s_var
{
	char	*key;
	char	*value;
	int		exported;
}			t_var;

/*
envptr		-> pointer to envp
envlst		-> pointer to t_list in t_minishell
status		-> last exit status
stratus		-> itoa'd status *(must be freed)*
prompt		-> for readline
envchild	-> for execve
*/
typedef struct s_info
{
	char	**envptr;
	t_list	*envlst;
	int		status;
	char	*stratus;
	char	*prompt;
	char	**envchild;
}			t_info;

/* ************************************************************************** */
/* -------------------------------- variables --------------------------------*/
/* ************************************************************************** */
/* assign_var.c */
// 
void	assign_var(t_list *env, char **args);
// 
/* var_values.c */
// 
char	*get_var_value(t_list *env, char *key);
void	add_or_update_var(t_list **env, char *key, char *value, int exported);
// 
/* var_utils.c */
// 
t_var	*new_var(char *key, char *value, int exported);
t_list	*find_var(t_list *env, char *key);
void	*dup_var(void *content);
void	del_var(void *content);
int		var_name_is_valid(char *key);
// 
/* shlvl.c */
// 
void	incr_shlvl(char *str);
void	init_shlvl(t_list *env);
// 
/* shellv.c */
// 
void	display_shell_vars(t_list *env);
// 
/* ************************************************************************** */
/* --------------------------------- builtins --------------------------------*/
/* ************************************************************************** */
/* builtin.c */
// 
void	execute_builtin(t_commands *cmd_table, t_list *env, char **envp);
// 
/* builtin_utils.c */
// 
int		is_secret_builtin(char *cmd);
int		is_valid_builtin(char *cmd);
// 
/* *************************************************************** echo ***** */
typedef struct s_echo_flags
{
	int	new_line;
	int	rainbow;
}	t_echo_flags;
// 
/* echo.c */
// 
void	mini_echo(char **args);
/* ***************************************************************** cd ***** */
// 
/* cd.c */
// 
void	mini_cd(t_list **env, char **args);
//
/* cd_utils.c */
// 
void	change_directory(t_list **env, const char *path);
// 
/* pwd.c */
// 
void	mini_pwd(t_list *env);
// 
/* export.c */
// 
void	handle_export(t_list *env, char **args);
// 
/* print_export.c */
// 
t_list	*copy_var_list(t_list *lst);
void	print_export(t_list *env);
// 
/* unset.c */
// 
void	unset_var(t_list **env, char *key);
void	process_unset(char **args, t_list *env);
// 
/* env_list.c */
// 
t_list	*init_env_list(char **envp);
void	set_envlst(t_list *env);
t_list	*get_envlist(void);
void	set_envptr(char **envp);
char	**get_envptr(void);
// 
/* print_env.c */
// 
void	print_env(t_list *env);
void	print_env_args(char **args);
// 
/* exit.c*/
// 
void	process_exit(char *input);
void	mini_exit(char **args);
// 
/* reset.c */
// 
void	reset_env(t_list **env, char **args, char **envp);
// 
/* ************************************************************************** */
/* --------------------------------- commands --------------------------------*/
/* ************************************************************************** */
/* commands.c */
// 
void	process_single_command(t_commands *cmd_table);
// 
/* path.c */
// 
t_list	*get_path_lst(t_list *env);
char	*get_cmd_path(const char *cmd, t_list *path_lst);
// 
/* child_env.c */
// 
char	**get_child_env(void);
// 
/* ************************************************************************** */
/* --------------------------------- signals ---------------------------------*/
/* ************************************************************************** */
/* signals.c */
// 
void	init_signals(void);
// 
/* signals_child.c */
// 
void	child_signals(void);
// 
/* ************************************************************************** */
/* -------------------------------- exit status ------------------------------*/
/* ************************************************************************** */
/* exit_status.c */
// 
void	set_exit_status(int exit_status);
int		get_exit_status(void);
char	*get_stratus(void);
// 
/* error_status.c */
// 
void	error_status(char *str, char *err_macro, int status);
void	ms_error_status(char *str, char *err_macro, int status);
void	ms_cmd_error_status(char *cmd, char *str, char *err_macro, int status);
// 
/* ************************************************************************** */
/* ---------------------------------- prompt ---------------------------------*/
/* ************************************************************************** */
/* prompt.c */
// 
void	set_prompt(void);
char	*get_prompt(void);
void	colorized_prmpt(void);
// 
/* ************************************************************************** */
/* ---------------------------------- utils ----------------------------------*/
/* ************************************************************************** */
/* info.c */
// 
t_info	*call_info(void);
void	destroy_all(void);
// 
#endif
