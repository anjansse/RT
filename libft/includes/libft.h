/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjansse <anjansse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:16:13 by anjansse          #+#    #+#             */
/*   Updated: 2019/12/17 12:24:59 by anjansse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 50

# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include "get_next_line.h"
# include "vec.h"
# include "ft_printf.h"

# define BOLD	"\x1b[1m"
# define ITALIC	"\x1b[3m"
# define UNDERL	"\x1b[4m"
# define CYAN	"\x1b[36m"
# define RED	"\x1b[91m"
# define GREEN	"\x1b[92m"
# define YELLOW	"\x1b[93m"
# define PURPLE	"\x1b[94m"
# define RESET	"\x1b[0m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
int					ft_array_len(char **array);
int					ft_verifstr(char *str, char *allowed);
uint32_t			ft_rgb(unsigned char r, unsigned char g, unsigned char b);
int					read_file(char *filename, char **content);
void				send_error(char *error);
char				*ft_capitalize(char *s);
char				*skip_ws(char *str);
int					*ft_range(int start, int end);
int					ft_strclen(char *str, char c);
int					ft_atoi(const char *str);
int					ft_stoi(char *n);
float				ft_stof(char *str);

void				ft_bzero(void *s1, size_t n);
int					ft_isws(char c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);

void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
uint32_t			ft_memtransform(uint32_t dst, char *src, unsigned int
		start, int len);

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(const char *s);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);

char				*ft_strappend(char *s1, char c);
char				*ft_strcat(char *s1, char *s2);
char				*ft_strchr(const char *s1, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *s1, char *s2);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjoinfree(char *s1, char *s2);
char				*ft_strjoinfree1(char *s1, char *s2);
char				*ft_strjoinfree2(char *s1, char *s2);
size_t				ft_strlcat(char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *s1, const char *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s1, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);

void				ft_swap(int *a, int *b);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);

void				ft_free_db_tab(char **av);

void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

#endif
