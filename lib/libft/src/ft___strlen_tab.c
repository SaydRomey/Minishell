/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___strlen_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:38:03 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/24 19:16:38 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Multiple strlen on TAB_SIZE amount of character strings within a pointers array.
*/
size_t	ft_strlen_tab(size_t tab_size, char **variables)
{
	size_t	total_l;
	size_t	x;

	total_l = 0;
	x = 0;
	if (tab_size == 0 || variables == NULL)
		return (total_l);
	while (x < tab_size)
		total_l += ft_strlen(variables[x++]);
	return (total_l);
}
