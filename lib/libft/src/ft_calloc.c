/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:31:08 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/04 21:47:11 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
allocates memory for an array of 'count' elements of 'size' bytes each
and returns a pointer to the allocated memory.
The memory is set to zero.
returns NULL if allocation fails
*must be freed*
*/
void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*allocated_memory;
	char	*memory_ptr;
	size_t	bytes_initialized;

	total_size = count * size;
	allocated_memory = malloc(total_size);
	if (allocated_memory == NULL)
		return (NULL);
	memory_ptr = (char *)allocated_memory;
	bytes_initialized = 0;
	while (bytes_initialized < total_size)
	{
		*memory_ptr = 0;
		memory_ptr++;
		bytes_initialized++;
	}
	return (allocated_memory);
}

/*
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	// ft_memset(ptr, 0, total_size);
	return (ptr);
}
*/
