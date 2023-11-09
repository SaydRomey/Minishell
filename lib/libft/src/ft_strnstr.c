/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:16:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 01:19:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
returns pointer to first occurence of 'little' in 'big'
(only first 'len' characters are searched)
returns NULL if 'little' is not found in 'big'
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	i;

	if (!big || !little)
		return (NULL);
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (*big != '\0' && len >= little_len)
	{
		i = 0;
		while (little[i] != '\0' && big[i] == little[i] && i < len)
			i++;
		if (i == little_len)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
