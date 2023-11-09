/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:33:23 by ppaquet           #+#    #+#             */
/*   Updated: 2023/11/08 09:42:36 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** -----
 * @brief Checks if the CHARACTER following a '$''s content meets the
 * requirements for	an eventual expansion process.
*/
bool	ms_is_expandable_content(char *content)
{
	size_t	i;

	i = 0;
	if (content == NULL)
		return (false);
	if (content[i + 1] != '\0'
		&& ft_iswhitespace(content[i + 1]) == false
		&& content[i + 1] != '$'
		&& content[i + 1] != '\"'
		&& content[i + 1] != '\''
		&& content[i + 1] != '/'
		&& content[i + 1] != '\\'
		&& content[i + 1] != '.'
		&& content[i + 1] != '='
		&& content[i + 1] != '('
		&& content[i + 1] != ')'
		&& ms_ismeta(content[i + 1]) == false)
		return (true);
	return (false);
}

/**
 * @brief Extracts the expandables <$***> from the string, build a pointers
 * array with variables.
*/
static char	**ms_extract_expandable_values(char *str_to_expand, size_t *c)
{
	char	**key_to_value_tab;
	size_t	x;

	if (str_to_expand == NULL || c == NULL)
		return (NULL);
	key_to_value_tab = NULL;
	if (str_to_expand == NULL)
		return (NULL);
	(*c) = ms_count_expandable_dollar(str_to_expand);
	key_to_value_tab = ft_alloc(CALLOC, ((*c) + 1), \
								sizeof(*key_to_value_tab));
	if (key_to_value_tab == NULL)
		return (NULL);
	ms_store_expandable_key(str_to_expand, key_to_value_tab);
	x = -1;
	while (key_to_value_tab[++x] != NULL)
		key_to_value_tab[x] = ms_find_corresponding_value(key_to_value_tab[x]);
	return (key_to_value_tab);
}

/** -----
 * @brief Builds the new character string by inserting the appropriate value(s)
 * from expandable key(s) originating from the command line.
*/
static char	*ms_insert_values(char **new, char **values, char *s)
{
	size_t	i;
	size_t	n;
	size_t	x;

	if (new == NULL || *new == NULL || values == NULL)
		return (NULL);
	i = 0;
	n = 0;
	x = -1;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ms_is_valid_expandable(&s[i]) == false)
			(*new)[n++] = s[i++];
		if (ms_is_valid_expandable(&s[i]) == true)
		{
			if (values[++x] != NULL)
			{
				ft_memcpy(&(*new)[n], values[x], ft_strlen(values[x]));
				n += ft_strlen(values[x]);
			}
			ms_skip_expandable_content(s, &i);
		}
	}
	(*new)[n] = '\0';
	return (*new);
}

/**
 * @brief Expands the key variables in a character string by replacing them with
 * corresponding values from the environment (or shell).
 */
char	*ms_expand(char *str_to_expand)
{
	char	**env_value_tab;
	size_t	key_amount;
	size_t	total_lenght;
	char	*new_expanded;

	key_amount = 0;
	env_value_tab = ms_extract_expandable_values(str_to_expand, &key_amount);
	if (env_value_tab == NULL)
		return (NULL);
	total_lenght = ms_strlen_exclude_expandables(str_to_expand);
	total_lenght += ft_strlen_tab(key_amount, env_value_tab);
	new_expanded = NULL;
	new_expanded = ft_alloc(CALLOC, (total_lenght + 1), sizeof(*new_expanded));
	if (new_expanded == NULL)
		return (NULL);
	ms_insert_values(&new_expanded, env_value_tab, str_to_expand);
	free(env_value_tab);
	env_value_tab = NULL;
	return (new_expanded);
}
