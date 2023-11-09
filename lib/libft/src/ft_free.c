/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:08:06 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/04 23:12:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
frees the memory of a pointer and sets it to NULL
(protects against double free)
*/
void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_matrix(int **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/* (with proof)
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printf("(freed)%s\n", split[i]);
		free(split[i]);
		i++;
	}
	ft_printf("elements freed: %d\n", i);
	free(split);
}
*/