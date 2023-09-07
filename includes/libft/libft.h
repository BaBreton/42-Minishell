/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:20:34 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 16:38:28 by cparras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define FORMAT "cspdiuxX%"
# define NOSUCH ": No such file or directory\n"

# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

/*---------------------------------------------------------------------------*/
typedef struct s_list
{
	char			*word;
	struct s_list	*next;
}					t_list;

/*---------------------------------------------------------------------------*/
t_list		*ft_lstnew(char	*content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*---------------------------------------------------------------------------*/
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *str);
int			ft_lstsize(t_list *lst);
/*---------------------------------------------------------------------------*/
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
/*---------------------------------------------------------------------------*/
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstdelone(t_list *lst);
/*---------------------------------------------------------------------------*/
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strcpy(char	*src);

/*---GNL---*/
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strwdup(char *str, int len);
char		*ft_loop(char *str1, char *str2);
int			have_n(char	*temp);
char		*print_line(char **temp);
char		*get_next_line(int fd);

/*---PRINTF---*/
int			thumb(char thumbnail, va_list args);
int			check_args(char next, va_list args);
int			brain(int *i, char now, char next, va_list args);
int			ft_putchar(int c);
int			ft_printf(const char *format, ...);
int			ft_putstr(char *s);
int			ft_putnbr(int nb);
int			ft_puthexa(unsigned int nb, char *base);
int			ft_adress(void *ptr);
int			ft_putunbr(unsigned int nb);

int			printerr(char *error, int option);
char		*new_str(char *str);
void		free_char(char **tab, int size);
int			_char(char c, char d);
int			_quote(char c, char d);
int			_space(char c);
int			_spec(char c, char d);
char		**double_chardup(char **str, int size);
char		**str_to_tab(char **tab, char *str, int size, int option);
int			get_char_size(char **tab);
int			count_lines(int fd);
char		*ft_strbjoin(char *s1, char *s2);
char		*get_base_path(char **ev);
void		erase_env(char **ev);
char		*get_homes_path(char **ev);

#endif