/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:24:29 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/21 01:33:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
applies the effect of 'function' to each character of the string 'str'
*/
void	ft_striteri(char *str, void (*function)(unsigned int, char *))
{
	size_t	i;

	if (!str || !function)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		function(i, &str[i]);
		i++;
	}
}
