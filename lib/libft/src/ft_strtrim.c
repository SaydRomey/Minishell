/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:06:07 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 01:20:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
checks if 'c' is in 'set'
*/
static int	is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
returns the index of the first character of 'str' that is not in 'set'
*/
static size_t	find_trimmed_start(const char *str, const char *set)
{
	size_t	start;

	start = 0;
	while (str[start] != '\0' && is_in_set(str[start], set) == TRUE)
		start++;
	return (start);
}

/*
returns the index of the last character of 'str' that is not in 'set'
*/
static size_t	find_trimmed_end(const char *str, const char *set, size_t start)
{
	size_t	end;

	end = 0;
	while (str[end] != '\0')
		end++;
	while (end > start && is_in_set(str[end - 1], set) == TRUE)
		end--;
	return (end);
}

/*
allocates memory for a copy of 'str' without the characters
specified in 'set' at the beginning and the end of the string
*/
static char	*allocate_and_copy(const char *str, size_t start, size_t end)
{
	char	*trimmed;
	size_t	trimmed_len;
	size_t	i;

	trimmed_len = end - start;
	trimmed = (char *)malloc(sizeof(char) * (trimmed_len + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < trimmed_len)
	{
		trimmed[i] = str[start + i];
		i++;
	}
	trimmed[trimmed_len] = '\0';
	return (trimmed);
}

/*
Allocates with malloc, returns a copy of 'str'
without the characters specified in 'set' 
at the beginning and the end of the string.
**must be freed*
*/
char	*ft_strtrim(const char *str, const char *set)
{
	size_t	start;
	size_t	end;

	if (!str || !set)
		return (NULL);
	start = find_trimmed_start(str, set);
	end = find_trimmed_end(str, set, start);
	return (allocate_and_copy(str, start, end));
}

/*
char	*ft_strtrim(const char *str, const char *set)
{
	char	*trimmed;
	size_t	start;
	size_t	end;

	if (!str || !set)
		return (NULL);
	start = 0;
	while (str[start] != '\0' && ft_strchr(set, str[start]) != NULL)
		start++;
	end = ft_strlen(str);
	while (end > start && ft_strchr(set, str[end - 1]) != NULL)
		end--;
	trimmed = ft_substr(str, start, end - start);
	return (trimmed);
}
*/

/*
char	*ft_strtrim(const char *str, const char *set)
{
	size_t	start;
	size_t	end;

	if (!str || !set)
		return (NULL);
	start = 0;
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	end = ft_strlen(str);
	while (end > start && ft_strchr(set, str[end - 1]))
		end--;
	return (ft_substr(str, start, end - start));
}
*/
