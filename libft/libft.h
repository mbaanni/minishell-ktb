/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:08:51 by mtaib             #+#    #+#             */
/*   Updated: 2023/06/09 18:37:38 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
/* Mandatory part */

int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_strlen(char *s);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_strchr(char *s, int c);
char					*ft_strrchr(char *s, int c);
int						ft_strncmp(char *s1, char *s2, size_t n);
char					*ft_strnstr(char *haystack, char *needle, int len);
int						ft_strlcpy(char *dst, char *src, int dstsize);
int						ft_strlcat(char *dst, char *src, int dstsize);
int						ft_atoi(char *str);
void					*ft_memset(void *b, int c, int len);
void					ft_bzero(void *s, int n);
void					*ft_memcpy(void *dst, void *src, int n);
void					*ft_memmove(void *dst, void *src, int len);
void					*ft_memchr(void *s, int c, int n);
int						ft_memcmp(void *s1, void *s2, int n);
void					*ft_calloc(int count, int size);
char					*ft_strdup(char *s1);

/* Additional funcitons */

char					*ft_substr(char *s, unsigned int start, int len);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strtrim(char *s1, char *set);
char					**ft_split(char *s, char c);
char					*ft_itoa(int n);
char					*ft_strmapi(char *s, char (*f)(unsigned int, char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;
typedef struct s_myalloc
{
	void				*content;
	struct s_myalloc	*next;
}						t_myalloc;

int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *node);
void					ft_lstadd_back(t_list **lst, t_list *node);
void					ft_lstiter(t_list *lst, void (*f)(void *));
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
void					garbage_collector(void *adress, int arg);
void					custom_exit(int exit_code);
int						ft_fdprintf(int fd, char *str, ...);

//my alloc
void					*my_alloc(int size);
t_myalloc				*my_alloc_new(void *content);
t_myalloc				*my_alloc_last(t_myalloc *lst);
void					my_alloc_addback(t_myalloc **lst, t_myalloc *node);
void					my_alloc_clear(t_myalloc **lst, void (*del)(void *));

#endif
