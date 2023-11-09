/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:26:19 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:19:22 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
applies the effect of 'function' to each character of 'str'
then returns the allocated new string
**must be freed*
*/
char	*ft_strmapi(const char *str, char (*function)(unsigned int, char))
{
	char	*new_str;
	size_t	new_len;
	int		i;

	if (!str || !function)
		return (NULL);
	new_len = (ft_strlen(str) + 1);
	new_str = (char *)malloc(sizeof(char) * new_len);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new_str[i] = (*function)(i, str[i]);
		i++;
	}
	*(new_str + i) = '\0';
	return (new_str);
}
