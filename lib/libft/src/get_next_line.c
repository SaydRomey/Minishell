/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:14:07 by cdumais           #+#    #+#             */
/*   Updated: 2023/10/21 00:56:09 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	update_str(char **str, char *newline_pos)
{
	char	*tmp;

	tmp = ft_strdup(newline_pos + 1);
	free(*str);
	*str = tmp;
	if (**str == '\0')
	{
		free(*str);
		*str = NULL;
	}
}

static char	*extract_line(char **str)
{
	char	*line;
	size_t	len;
	char	*newline_pos;

	if (!*str)
		return (NULL);
	newline_pos = ft_strchr(*str, '\n');
	if (newline_pos)
	{
		len = newline_pos - *str;
		line = ft_substr(*str, 0, len);
		update_str(str, newline_pos);
	}
	else
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (LOOP)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (NULL);
	return (extract_line(&str));
}

/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: could not open file %s\n", argv[1]);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
*/
