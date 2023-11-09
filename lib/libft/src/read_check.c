/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:13:46 by cdumais           #+#    #+#             */
/*   Updated: 2023/09/14 15:19:29 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
opens a file, attempts to read 1 byte from it
returns:
 'EMPTY' (0) -> file is empty
 'VALID' (1) -> file is not empty
 'ERROR' (-1) -> problem opening or reading from the file
*/
int	read_check(const char *filename)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(filename, READ);
	if (fd < 0)
		return (ERROR);
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read == 0)
		return (EMPTY);
	else if (bytes_read == -1)
		return (ERROR);
	return (VALID);
}

/*
int	main(int argc, char **argv)
{
	int	check;

	if (argc != 2)
		va_exit_error("Usage: %s file", argv[0]);
	check = read_check(argv[1]);
	if (check == ERROR)
		va_exit_error("Error opening or reading file [%s]", argv[1]);
	else if (check == EMPTY)
		va_exit_error("Error: file [%s] is empty", argv[1]);
	return (SUCCESS);
}
*/
