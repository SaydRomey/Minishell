/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:15:34 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/24 15:21:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
allocates memory for a copy of the string 'src'
and returns a pointer to it.
*must be freed*
*/
char	*ft_strdup(const char *src)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len] != '\0')
		len++;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		new_str[i] = src[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

/* 
char	*ft_strdup(const char *src)
{
	char	*new_str;
	size_t	str_len;
	
	if (!src)
		return (NULL);
	str_len = ft_strlen(src) + 1;
	new_str = ft_calloc(str_len, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, src, str_len);
	return (new_str);
}
*/
