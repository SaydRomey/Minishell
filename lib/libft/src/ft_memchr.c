/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:16:44 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 01:08:48 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
search for 'c' in the first 'n' bytes of 's'
return a pointer to the byte if found
or NULL if not found
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;
	unsigned char		target;

	if (!s)
		return (NULL);
	i = 0;
	src = (const unsigned char *)s;
	target = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == target)
			return ((void *)src + i);
		i++;
	}
	return (NULL);
}
