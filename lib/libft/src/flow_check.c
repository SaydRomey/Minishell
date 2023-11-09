/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:45:58 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/09 17:36:07 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
returns TRUE if ft_itoa and ft_atoi return different values
** usage: int overflow = flow_check("2147483648"); *
*/
int	flow_check(char *input)
{
	char	*output;

	output = ft_itoa(ft_atoi(input));
	if (ft_strncmp(input, output, ft_strlen(input)) != SAME)
		return (free(output), TRUE);
	return (free(output), FALSE);
}

/*
int main(int argc, char **argv)
{
	int i;
	int overflow;

	i = 1;
	if (argc < 2)
		exit_error("too few arguments");
	while (i < argc)
	{
		overflow = flow_check(argv[i]);
		if (overflow == TRUE)
		{
			printf("flow_check: %s is not an int\n", argv[i]);
			return (FAILURE);
		}
		i++;
	}
	printf("flow_check: all arguments are ints\n");
	return (SUCCESS);
}
*/
