/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___free_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:23:55 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/24 19:15:54 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_free_tab(char ***to_free, size_t size)
{
	size_t	x;

	x = -1;
	if (to_free == NULL || (*to_free) == NULL)
		return ;
	while (++x < size)
	{
		if ((*to_free)[x] != NULL)
		{
			free((*to_free)[x]);
			(*to_free)[x] = NULL;
		}
	}
	free(*to_free);
	*to_free = NULL;
	return ;
}
