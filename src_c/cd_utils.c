/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:16:14 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 08:32:41 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
sets the 'OLDPWD' variable to the current working directory
if 'PWD' doesn't exist, sets 'OLDPWD' to an empty string
*/
static void	set_oldpwd(t_list **env)
{
	char	*oldpwd;

	oldpwd = get_var_value(*env, "PWD");
	if (oldpwd)
		add_or_update_var(env, "OLDPWD", oldpwd, TRUE);
	else
		add_or_update_var(env, "OLDPWD", "", TRUE);
}

/*
sets the 'PWD' variable to the current working directory
*/
static void	set_pwd(t_list **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ms_error_status("cd", strerror(errno), 1);
		return ;
	}
	add_or_update_var(env, "PWD", cwd, TRUE);
}

/*
change directory to the specified path
*/
void	change_directory(t_list **env, const char *path)
{
	if (chdir(path) != SUCCESS)
	{
		ms_cmd_error_status("cd", (char *)path, strerror(errno), 1);
		return ;
	}
	set_oldpwd(env);
	set_pwd(env);
}
