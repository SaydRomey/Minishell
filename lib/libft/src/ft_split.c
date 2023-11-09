/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:26:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/24 15:21:20 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
returns 'count'
incremented if the current char is not the separator 
and the next char is the separator or the end of the string
(used to malloc the right size for the array of word_count)
*/
static size_t	get_word_count(const char *str, char c)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

/*
returns an allocated copy of the word between 'start' and 'end'
*/
static char	*copy_word(const char *start, const char *end)
{
	size_t	len;
	char	*word;
	size_t	i;

	len = end - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

/*
used to extract a word from 'str'
and update pointer to the next potential word
*/
static char	*get_next_word(const char *str, char c, const char **new_position)
{
	const char	*word_start;

	word_start = str;
	while (*str != c && *str != '\0')
		str++;
	*new_position = str;
	return (copy_word(word_start, str));
}

/*
frees the array of strings
(already in libft)
*/
// static void	free_split(char **split)
// {
// 	int	i;

// 	i = 0;
// 	while (split[i] != NULL)
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// }

/*
returns an array of strings, 
each string being a word from 'str' separated by 'c'
**must be freed (using free_split)*
*/
char	**ft_split(const char *str, char c)
{
	char	**split_strings;
	size_t	word_count;
	size_t	i;

	word_count = get_word_count(str, c);
	split_strings = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!split_strings)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		if (*str != c)
		{
			split_strings[i] = get_next_word(str, c, &str);
			if (!split_strings[i])
				return (free_split(split_strings), NULL);
			i++;
		}
		else
			str++;
	}
	split_strings[i] = NULL;
	return (split_strings);
}
