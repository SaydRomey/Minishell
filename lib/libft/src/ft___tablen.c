/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___tablen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:21:33 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/10 11:12:15 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_tablen(char **tab)
{
	size_t	l;

	l = 0;
	if (tab == NULL)
		return (l);
	while (tab[l] != NULL)
		l++;
	return (l);
}
