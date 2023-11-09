/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:49:30 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 15:06:05 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "libft_utils.h" // structs, macros, includes and typedefs
# include <stdbool.h> // boolean values (for po)

/* ********************************* Functions ****************************** */
// 
int		ft_isalpha(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
// 
int		ft_isdigit(int c);
int		ft_str_isdigit(char *str);
int		ft_isxdigit(int c);
// 
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
// int  ft_ispunct(int c);
// 
int		ft_isspace(int c);
int		ft_isblank(int c);
// 
int		ft_tolower(int c);
int		ft_toupper(int c);
// 
size_t	ft_strlen(const char *str);
// 
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
// 
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// 
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
int		ft_strsame(const char *s1, const char *s2);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
// 
int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int base);
// 
/* ************************** Functions using malloc ************************ */
// 
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strjoin_with(char *s1, char *s2, char *delimiter);
char	*ft_strtrim(const char *str, const char *set);
char	**ft_split(const char *str, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *str, char (*function)(unsigned int, char));
// 
/* ************************** Functions using write ************************* */
// 
void	ft_striteri(char *str, void (*function)(unsigned int, char *));
size_t	ft_putchar_fd(char c, int fd);
size_t	ft_putstr_fd(char *str, int fd);
size_t	ft_putendl_fd(char *str, int fd);
size_t	ft_putnbr_fd(int n, int fd);
//
size_t	ft_putchar(char c);
size_t	ft_putstr(char *str);
size_t	ft_putendl(char *str);
size_t	ft_putnbr(int n);
// 
/* ****************************** Linked list ******************************* */
//
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstremoveone(t_list **head, t_list *to_remove, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
//
t_list	*ft_lstcpy(t_list *lst, t_dup_fptr dup_cont, t_del_fptr del_cont);
// 
void	ft_lstswap(t_list *a, t_list *b);
// void	ft_lstswap_nodes(t_list **head, t_list *a, t_list *b);
void	ft_lstswitch(t_list **head, t_list *a, t_list *b);
t_list	*ft_lstsort(t_list *lst, t_cmp cmp_func);
// void	ft_lstsort_list(t_list *lst, t_cmp cmp_func);
// 
/* ********************************** GNL *********************************** */
//
char	*get_next_line(int fd);
//
/*	****************************** ft_printf ******************************** */
//
int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *str, ...);
int		ft_vprintf(const char *str, va_list args);
int		ft_vfprintf(int fd, const char *str, va_list args);
int		ft_intlen(int n);
size_t	ft_putnbr_base_fd(size_t n, int fd, const char *base_format);
//
/* ******************************** Pushwap ********************************* */
// 
void	ft_swap(int *a, int *b);
int		ft_min(int this, int that);
int		ft_max(int this, int that);
// 
/* *********************************** FDF ********************************** */
// 
int		ft_abs(int n);
float	ft_fabs(float n);
// 
void	exit_error(char *msg);
void	va_exit_error(const char *msg, ...);
void	exit_perror(const char *msg);
// 
void	safe_free(void **ptr);
void	free_split(char **split);
void	free_matrix(int **matrix);
// 
/* ********************************** MISC ********************************** */
// 
int		flow_check(char *input);
int		read_check(const char *filename);
int		char_count(char *str, char c);
// 
/* ********************************** FUN *********************************** */
// 
void	ft_strainbow(char *str, int new_line);
char	*color_str(char *str, char *color_code);
// 
// *********************************************************************** PO //

enum e_alloc_type
{
	CALLOC,
	MALLOC
};

int		ft_strcmp(const char *s1, const char *s2);
bool	ft_atoi_check(int *res, const char *str, bool (*f)(void *));
bool	ft_iswhitespace(int c);
void	*ft_alloc(enum e_alloc_type type, size_t count, size_t size);
char	*ft_strstr(const char *haystack, const char *needle);
size_t	ft_strlen_tab(size_t tab_size, char **variables);
size_t	ft_tablen(char **tab);
void	ft_free_tab(char ***to_free, size_t size);
//
#endif
