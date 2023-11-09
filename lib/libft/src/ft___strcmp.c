/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___strcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:54:18 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/10 11:12:10 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (tmp1[i] != '\0' && tmp2[i] != '\0')
	{
		if (tmp1[i] != tmp2[i])
			return (tmp2[i] - tmp1[i]);
		i++;
	}
	if (tmp1[i] != tmp2[i])
		return (tmp2[i] - tmp1[i]);
	return (0);
}
