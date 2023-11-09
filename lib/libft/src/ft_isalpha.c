/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:42:38 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/29 17:52:13 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (TRUE);
	else
		return (FALSE);
}

int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (TRUE);
	else
		return (FALSE);
}

int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (TRUE);
	else
		return (FALSE);
}

/*
int	ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (TRUE);
	else
		return (FALSE);
}
*/
