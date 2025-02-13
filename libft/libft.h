/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talin <talin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:31:06 by talin             #+#    #+#             */
/*   Updated: 2024/10/07 15:58:23 by talin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef LIMIT
#  define LIMIT 1024
# endif

typedef struct t_format
{
	int		plus;
	int		minus;
	int		space;
	int		zero;
	int		dot;
	int		width;
	int		precision;
	int		neg_prec;
	int		sharp;
	char	specifier;
}	t_format;

# define SPECIFIER	"cspdiuxX%"
# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"

int			ft_printf(const char *str, ...);
char		*ft_strchr_pr(char *s, int c);
int			ft_isdigit_pr(int c);
int			ft_atoi_pr(char *str);
t_format	ft_newformat(void);
int			ft_print_format(t_format new, va_list ptr);
int			ft_strlen_pr(char *str);
int			ft_putnstr(char *str, int size);
int			ft_putnchar(int c, int size);
char		*ft_strdup_pr(char *s);
int			ft_printf_str(t_format new, va_list ptr);
int			ft_printf_char(t_format new, va_list ptr);
int			ft_putchar_pr(char c);
int			ft_parse(char *str, va_list ptr);
int			ft_printf_int(t_format new, va_list ptr);
char		ft_sign(t_format new, int neg);
int			ft_printf_uint(t_format new, va_list ptr);
int			ft_printf_ptr(t_format new, va_list ptr);
int			ft_recursive_hex(t_format new, size_t n, size_t i);
int			ft_nbrlen(size_t n);
int			ft_printf_hex(t_format new, va_list ptr);
char		*get_next_line(int fd);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strchr_gnl(const char *s, int c);
int			ft_atoi(const char *nptr);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_putchar_fd(char c, int fd);
char		*ft_itoa(int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
