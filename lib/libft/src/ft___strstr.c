/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___strstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:50:05 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/24 19:16:47 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (haystack == NULL || needle == NULL)
		return (NULL);
	tmp = (char *)haystack;
	while (needle[i] != '\0')
	{
		if (tmp[i] != needle[i] || tmp[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&tmp[i]);
}
