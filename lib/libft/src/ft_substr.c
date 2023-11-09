/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:49:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 01:20:52 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
allocates with malloc and returns a substring from the string ’s’
The substring begins at index ’start’ and is of maximum size ’len’
return NULL if the allocation fails
*must be freed*
*/
char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	str_len;
	size_t	i;

	if (!str)
		return (NULL);
	str_len = 0;
	while (str[str_len] != '\0')
		str_len++;
	if (start >= str_len)
		return (NULL);
	if (len > (str_len - start))
		len = str_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (start >= str_len)
		return (NULL);
	if (len > (str_len - start))
		len = str_len - start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, str + start, len + 1);
	return (substr);
}
*/
