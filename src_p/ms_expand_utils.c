/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:08 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:43:10 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Takes over the parsing, continues the iteration while there are
 * repeating unexpandable '$' symbols.
*/
void	ms_skip_multi_dollar(char *str_to_expand, size_t *i)
{
	if (str_to_expand == NULL || i == NULL)
		return ;
	while (str_to_expand[*i] != '\0' && str_to_expand[*i] == '$')
	{
		(*i)++;
		if (str_to_expand[*i] != '\0' && str_to_expand[(*i) + 1] != '$')
			break ;
	}
	return ;
}

/** -----
 * @brief Checks if the character is '$'; Then checks if it is an
 * expandable KEY.
*/
bool	ms_is_valid_expandable(char *possible_key)
{
	int	i;

	i = 0;
	if (possible_key[i] == '$'
		&& ms_is_expandable_content(&possible_key[i]) == true)
		return (true);
	return (false);
}

/** -----
 * @brief Searches for valid expandables to expand; Stores them in the
 * pointers array.
*/
char	**ms_store_expandable_key(char *str_to_expand, char **variables)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (str_to_expand == NULL || variables == NULL)
		return (NULL);
	while (str_to_expand[i] != '\0')
	{
		if (ms_is_valid_expandable(&str_to_expand[i]) == true)
			variables[y++] = (char *)&str_to_expand[i];
		i++;
	}
	return (variables);
}

/**
 * @brief Finds the corresponding value for '?' or '0'.
*/
static char	*check_additional_key(char *key)
{
	if (key == NULL || *key == '\0')
		return (NULL);
	if (key[0] == '?')
		return (get_stratus());
	else if (key[0] == '0')
		return (SNEAKY_MESSAGE);
	return (NULL);
}

/** -----
 * @brief Uses the functions that returns the right variable's value from
 * the current environment, or shell.
*/
char	*ms_find_corresponding_value(char *expandable_key)
{
	char		*key;
	char		*environment_value;
	size_t		i;

	i = 0;
	if (expandable_key == NULL)
		return (NULL);
	ms_skip_expandable_content(expandable_key, &i);
	key = ft_alloc(CALLOC, i, sizeof(*key));
	if (key == NULL)
		return (NULL);
	ft_strlcpy(key, &expandable_key[1], i);
	environment_value = get_var_value(get_envlist(), key);
	if (environment_value == NULL)
		environment_value = check_additional_key(key);
	free(key);
	key = NULL;
	return (environment_value);
}
