/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:31:15 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/03 11:39:03 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
returns the number of instances of 'c' in 'str'
*/
int	char_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count += 1;
		i++;
	}
	return (count);
}
