/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___iswhitespace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:25:59 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/10 11:12:08 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

bool	ft_iswhitespace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}
