/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:14:51 by cdumais           #+#    #+#             */
/*   Updated: 2023/08/30 12:14:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
returns the length of the base
(edge case of n = 0 is handled in ft_putnbr_base_fd)
*/
static size_t	get_base_length(size_t n, size_t base_len)
{
	size_t	length;

	length = 0;
	while (n)
	{
		n = n / base_len;
		length++;
	}
	return (length);
}

/*
iterative implementation (with buffer)
*/
size_t	ft_putnbr_base_fd(size_t n, int fd, const char *base_format)
{
	char	buffer[65];
	size_t	base_len;
	size_t	num_len;
	ssize_t	out;
	size_t	i;

	base_len = ft_strlen(base_format);
	num_len = get_base_length(n, base_len);
	out = 0;
	if (n == 0)
		return (ft_putchar_fd(base_format[0], fd));
	i = 0;
	while (i < num_len)
	{
		buffer[num_len - 1 - i] = base_format[n % base_len];
		n = n / base_len;
		i++;
	}
	i = 0;
	while (i < num_len)
	{
		out += ft_putchar_fd(buffer[i], fd);
		i++;
	}
	return (out);
}

/*
iterative version (no buffer/reversed)
*/
/*
size_t	ft_putnbr_base_fd(size_t n, int fd, const char *base_format)
{
	size_t	base_len;
	size_t	num_len;
	size_t	out;
	size_t	power;
	size_t	i;

	base_len = ft_strlen(base_format);
	num_len = get_base_length(n, base_len);
	out = 0;
	if (n == 0)
		return (ft_putchar_fd(base_format[0], fd));
	while (num_len > 0)
	{
		power = 1;
		i = 1;
		while (i < num_len)
		{
			power *= base_len;
			i++;
		}
		out += ft_putchar_fd(base_format[n / power], fd);
		n = n % power;
		num_len--;
	}
	return (out);
}
*/

/*
recursive implementation
*/
/*
size_t	ft_putnbr_base_fd(size_t n, int fd, const char *base_format)
{
	size_t	out;
	size_t	base;

	base = ft_strlen(base_format);
	out = 0;
	if (n < base)
		out += ft_putchar_fd(base_format[n % base], fd);
	else
	{
		out += ft_putnbr_base_fd(n / base, fd, base_format);
		out += ft_putnbr_base_fd(n % base, fd, base_format);
	}
	return (out);
}
*/
