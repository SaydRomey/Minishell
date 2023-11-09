/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:06:02 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/10 10:05:43 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
reverses the order of the digits in the buffer
*/
static void	reverse_buffer(char *buffer, int num_digits)
{
	int		start;
	int		end;
	char	tmp;

	start = 0;
	end = num_digits - 1;
	while (start < end)
	{
		tmp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = tmp;
		start++;
		end--;
	}
}

/*
fills the buffer with the digits of n
stores the digit in the buffer in reverse order
returns the number of digits
*/
static int	fill_buffer(int n, char *buffer)
{
	int	num_digits;
	int	tmp;
	int	digit;

	num_digits = 0;
	tmp = n;
	while (tmp > 0)
	{
		digit = tmp % 10;
		buffer[num_digits] = digit + '0';
		num_digits++;
		tmp /= 10;
	}
	return (num_digits);
}

/*
iterative implementation of ft_putnbr_fd
returns the number of digits printed
outputs the number n to the given file descriptor
*/
size_t	ft_putnbr_fd(int n, int fd)
{
	size_t	size;
	int		num_digits;
	char	buffer[12];

	if (n == 0)
		return (write(fd, "0", 1));
	if (n == INT_MIN)
		return (write(fd, "-2147483648", 11));
	size = 0;
	if (n < 0)
	{
		size += write(fd, "-", 1);
		n = -n;
	}
	num_digits = fill_buffer(n, buffer);
	reverse_buffer(buffer, num_digits);
	size += write(fd, buffer, num_digits);
	return (size);
}

/*
calls 'ft_putnbr_fd' on standard output
returns the number of digits printed
*/
size_t	ft_putnbr(int n)
{
	return (ft_putnbr_fd(n, FD_OUTPUT));
}

/* recursive implementation of ft_putnbr_fd
returns the number of digits printed
outputs the number n to the given file descriptor

size_t	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		ft_putchar_fd(n + '0', fd);
	}
	return (ft_intlen(n));
}
*/
