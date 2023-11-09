/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:46:41 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/03 11:43:59 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	get_value(char c)
{
	char	*base_lower;
	char	*base_upper;
	int		i;

	base_lower = HEX_LO;
	base_upper = HEX_UP;
	i = 0;
	while (base_lower[i])
	{
		if (c == base_lower[i] || c == base_upper[i])
			return (i);
		i++;
	}
	return (ERROR);
}

static int	check_sign(const char *str, int *index)
{
	int	sign;

	sign = 1;
	if (str[*index] == '-')
	{
		sign = -1;
		(*index)++;
	}
	else if (str[*index] == '+')
	{
		*index = *index + 1;
	}
	return (sign);
}

/*
Converts a string to an integer
according to the given base
overflow: undefined behavior
*/
int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	i;
	int	value;

	if (!str || base < 2 || base > 16)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = check_sign(str, &i);
	result = 0;
	while (str[i])
	{
		value = get_value(str[i]);
		if (value == ERROR || value >= base)
			break ;
		result = result * base + value;
		i++;
	}
	return (result * sign);
}
