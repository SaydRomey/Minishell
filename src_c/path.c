/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:17:04 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/09 11:19:42 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
returns a series of paths from the PATH variable
or NULL if the variable doesn't exist
*/
static char	**split_path(t_list *env)
{
	char	*env_path_value;
	char	**path_array;

	env_path_value = get_var_value(env, "PATH");
	if (env_path_value)
	{
		path_array = ft_split(env_path_value, ':');
		return (path_array);
	}
	return (NULL);
}

/*
returns a list of paths from the PATH variable
or NULL if the variable doesn't exist or is empty
*/
t_list	*get_path_lst(t_list *env)
{
	char	**path_array;
	t_list	*path_lst;
	t_list	*new_node;
	int		i;

	path_lst = NULL;
	path_array = split_path(env);
	if (path_array)
	{
		i = 0;
		while (path_array[i] != NULL)
		{
			new_node = ft_lstnew(ft_strdup(path_array[i]));
			ft_lstadd_back(&path_lst, new_node);
			i++;
		}
		free_split(path_array);
		return (path_lst);
	}
	return (NULL);
}

/*
returns the full path of the given command
or NULL if the command doesn't exist
prints an error message if the command doesn't exist (127)
or if the user doesn't have permission to execute it (126)
*/
char	*get_cmd_path(const char *cmd, t_list *path_lst)
{
	char	*possible_path;
	char	*full_cmd_path;

	while (path_lst)
	{
		possible_path = ft_strjoin((char *)path_lst->content, "/");
		full_cmd_path = ft_strjoin(possible_path, cmd);
		free(possible_path);
		if (access(full_cmd_path, F_OK) == 0)
			return (full_cmd_path);
		free(full_cmd_path);
		path_lst = path_lst->next;
	}
	if (access(cmd, F_OK) == SUCCESS && ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) != SUCCESS)
			return (ms_error_status((char *)cmd, ERR_NO_PERM, 126), NULL);
		full_cmd_path = ft_strdup(cmd);
		return (full_cmd_path);
	}
	return (ms_error_status((char *)cmd, ERR_BAD_CMD, 127), NULL);
}
