/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:02:10 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/29 17:47:13 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Converts a string of characters to integer
ignores leading whitespaces
handles the signs of the integer
overflow: undefined behavior
*/
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]) == TRUE)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/* same as above, but with no helper function 

int ft_atoi(const char *str)
{
	int result;
	int sign;
	int i;

	result = 0;
	sign = 1;
	i = 0;
	if (str == NULL)
		return (0);
	// skip leading whitespace
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	// check for optional sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	// convert digits to integer until non-digit is found
	while (str[i] >= '0' && str[i] <= '9')
	{
		// convert the char to int and update result
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
*/

/* pointer arithmetics, no helper functions

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - '0';
	return (result * sign);
}
*/
