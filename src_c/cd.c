/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:34:16 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 08:32:56 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
changes directory to the home directory
*/
static void	cd_to_home(t_list **env)
{
	char	*home_path;
	t_list	*exported_home;

	home_path = get_var_value(*env, "HOME");
	if (!home_path)
	{
		ms_error_status("cd", ERR_NOHOME, 1);
		return ;
	}
	exported_home = find_var(*env, "HOME");
	if (exported_home && ((t_var *)exported_home->content)->exported == TRUE)
		change_directory(env, home_path);
}

/*
change directory to 'OLDPWD'
also prints it in the terminal
*/
static void	cd_to_oldpwd(t_list **env)
{
	char	*previous_path;

	previous_path = get_var_value(*env, "OLDPWD");
	if (!previous_path)
	{
		ms_error_status("cd", ERR_OLDPWD, 1);
		return ;
	}
	ft_printf("%s\n", previous_path);
	change_directory(env, previous_path);
	set_exit_status(SUCCESS);
}

/*
handles the 'cd' command.
if no argument or '~', navigate to the home directory.
if arg is '-', navigate to 'OLDPWD' from env
*/
void	mini_cd(t_list **env, char **args)
{
	if (!args[1] || ft_strcmp(args[1], "~") == SAME)
		cd_to_home(env);
	else if (ft_strcmp(args[1], "-") == SAME)
		cd_to_oldpwd(env);
	else
		change_directory(env, args[1]);
}
