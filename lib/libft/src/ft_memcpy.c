/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:25:46 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 01:11:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Copies n bytes from memory area src to memory area dst.
If dst and src overlap, behavior is undefined.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (!dst || !src)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	while (n > 0)
	{
		*dst_ptr = *src_ptr;
		dst_ptr++;
		src_ptr++;
		n--;
	}
	return (dst);
}
