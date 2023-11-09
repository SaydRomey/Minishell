/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:35 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 17:47:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H

/* headers */

# include <unistd.h> // write, read, close
# include <stdlib.h> // malloc, free, exit
# include <string.h> // size_t, NULL, strerror
# include <stdio.h> // printf, size_t, NULL, perror
# include <fcntl.h> // open, read, write, close
# include <stdarg.h> // va_list, va_start, va_arg, va_end

/* structs */

// linked list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// for ft_lstswitch
typedef struct s_swap
{
	t_list	*a;
	t_list	*b;
	t_list	*prev_a;
	t_list	*prev_b;
}			t_swap;

// for ft_strainbow
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

/* function pointers */

// comparison function pointer
typedef int					(*t_cmp)(t_list *, t_list *);

typedef void				*(t_dup_fptr)(void *);
typedef void				(*t_del_fptr)(void *);

/* abbreviated data types*/

typedef signed char			t_s8;
typedef unsigned char		t_u8;
typedef const unsigned char	t_cu8;

typedef signed short		t_s16;
typedef unsigned short		t_u16;

typedef signed int			t_s32;
typedef unsigned int		t_u32;

typedef signed long long	t_s64;
typedef unsigned long long	t_u64;

/* numeral bases */

# define BINARY		"01"
# define OCTAL		"01234567"
# define DECIMAL	"0123456789"
# define HEX_LO		"0123456789abcdef"
# define HEX_UP		"0123456789ABCDEF"

/* GNL */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# endif

/* get with bash: 'ulimit -n' */
# ifndef OPEN_MAX
#  define OPEN_MAX	1024
# endif

# ifndef INT_MAX
#  define INT_MAX	2147483647
# endif

# ifndef INT_MIN
#  define INT_MIN	-2147483648
# endif

# ifndef PATH_MAX
#  define PATH_MAX	4096
# endif

# define TRUE	1
# define FALSE	0

// for toggle function
# define ON		1
# define OFF	0

// for read_check
# define VALID	1
# define EMPTY	0

// use with ft_strncmp
# define SAME	0

// infinite loop (while TRUE)
# define LOOP	1

/* Return values */

// successful exit status
# define SUCCESS	0
// failing exit status
# define FAILURE	1
// error exit status
# define ERROR		-1

/* Standard File Descriptors */

// STDIN_FILENO
# define FD_INPUT	0
// STDOUT_FILENO
# define FD_OUTPUT	1
// STDERR_FILENO
# define FD_ERROR	2

/* Pipe ends */

# define READ_END	0
# define WRITE_END	1

/* Standard File Permissions */

# define READ O_RDONLY
# define WRITE O_WRONLY
# define READ_WRITE O_RDWR
# define CREATE O_CREAT
# define TRUNCATE O_TRUNC
# define APPEND O_APPEND

/* ANSI escape codes */

// for ft_strainbow
# define RGB		"\033[38;2;"

# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define ITALIC		"\033[3m"

// # define RED		"\033[31m"
// # define GREEN		"\033[32m"
// # define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"

/* 256 colors */

# define GREEN		"\033[38;5;46m"
# define TURQUOISE	"\033[38;5;51m"
# define INDIGO		"\033[38;5;54m"
# define VIOLET		"\033[38;5;93m"
# define LAVENDER	"\033[38;5;140m"
# define RED		"\033[38;5;196m"
# define PINK		"\033[38;5;211m"
# define ORANGE		"\033[38;5;214m"
# define YELLOW		"\033[38;5;226m"

#endif
