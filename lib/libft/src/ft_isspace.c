/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:54:45 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/29 17:56:13 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || 
		c == '\v' || c == '\f' || c == '\r')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (TRUE);
	else
		return (FALSE);
}

/*
int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
*/
