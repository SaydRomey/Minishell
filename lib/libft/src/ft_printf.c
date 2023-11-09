/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:51:47 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/07 00:55:47 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	check_format(va_list args, char *str, int i, int fd)
{
	int	len;

	len = 0;
	if (str[i] == 'c')
		len = ft_putchar_fd(va_arg(args, int), fd);
	else if (str[i] == 's')
		len = ft_putstr_fd(va_arg(args, char *), fd);
	else if (str[i] == 'p')
	{
		len = ft_putstr_fd("0x", fd);
		len += ft_putnbr_base_fd(va_arg(args, unsigned long long), fd, HEX_LO);
	}
	else if (str[i] == 'd' || str[i] == 'i')
		len = ft_putnbr_fd(va_arg(args, int), fd);
	else if (str[i] == 'u')
		len = ft_putnbr_base_fd(va_arg(args, unsigned int), fd, DECIMAL);
	else if (str[i] == 'x')
		len = ft_putnbr_base_fd(va_arg(args, unsigned int), fd, HEX_LO);
	else if (str[i] == 'X')
		len = ft_putnbr_base_fd(va_arg(args, unsigned int), fd, HEX_UP);
	else if (str[i] == '%')
		len = write(fd, "%", 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, str);
	i = -1;
	len = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			len += check_format(args, (char *)str, i + 1, FD_OUTPUT);
			i++;
		}
		else
			len += write(FD_OUTPUT, &str[i], 1);
	}
	va_end(args);
	return (len);
}

/*
same as ft_printf but writes to a file descriptor
*/
int	ft_fprintf(int fd, const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, str);
	i = -1;
	len = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			len += check_format(args, (char *)str, i + 1, fd);
			i++;
		}
		else
			len += write(fd, &str[i], 1);
	}
	va_end(args);
	return (len);
}

/*
same as ft_printf but takes a va_list as argument
*/
int	ft_vprintf(const char *str, va_list args)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			len += check_format(args, (char *)str, i + 1, FD_OUTPUT);
			i++;
		}
		else
			len += write(FD_OUTPUT, &str[i], 1);
	}
	return (len);
}

/*
same as ft_printf but takes a va_list as argument
and writes to a file descriptor
*/
int	ft_vfprintf(int fd, const char *str, va_list args)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			len += check_format(args, (char *)str, i + 1, fd);
			i++;
		}
		else
			len += write(fd, &str[i], 1);
	}
	return (len);
}
