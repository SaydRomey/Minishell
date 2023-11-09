/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft___alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:35:41 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/24 19:24:46 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_alloc(enum e_alloc_type type, size_t count, size_t size)
{
	void	*ptr;
	int		attempts;

	ptr = NULL;
	attempts = 0;
	while (ptr == NULL && attempts++ < 10000)
	{
		if (type == 1)
			ptr = malloc(count * size);
		else if (type == 0)
			ptr = ft_calloc(count, size);
	}
	return (ptr);
}
