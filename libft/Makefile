# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 13:09:08 by mtaib             #+#    #+#              #
#    Updated: 2022/10/29 17:14:29 by mtaib            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c  ft_bzero.c ft_calloc.c ft_isalnum.c  ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c\
	ft_toupper.c ft_fdprintf.c get_next_line.c get_next_line_utils.c my_alloc.c\
	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c  myalloc_list.c

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

AR = ar -rcs

all : $(NAME)

$(NAME) : $(OBJ)
	@$(AR) $@ $^

%.o:%.c
	@cc -c $(CFLAGS)  $< 

clean :
	@rm -f *.o
fclean :  
	@rm -f *.o  $(NAME)
re :fclean all

.PHONY : all clean fclean re
