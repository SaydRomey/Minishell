/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:02:32 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/03 11:45:19 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
returns the absolute value of 'n'
*/
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/*
returns the absolute value of 'n'
*/
float	ft_fabs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}
