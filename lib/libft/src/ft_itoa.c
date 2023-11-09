/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:09:32 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:09:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
converts an integer to a string
**must be freed*
*/
char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		int_length;

	num = (long)n;
	if (num == 0)
		return (ft_strdup(""));
	int_length = ft_intlen(n);
	str = (char *)malloc(int_length + 1);
	if (!str)
		return (NULL);
	if (num == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (num < 0)
		num = -num;
	str[int_length] = '\0';
	while (int_length--)
	{
		str[int_length] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
