# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghpar <sanghpar@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 19:00:19 by sanghpar          #+#    #+#              #
#    Updated: 2021/07/01 19:35:42 by sanghpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

FILES = ft_strlen.c \
		ft_atoi.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strcat.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strstr.c \
		ft_strcmp.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strchr.c	\
		ft_strrchr.c \
		ft_strnstr.c \
		ft_isalpha.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isascii.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memcmp.c	\
		ft_calloc.c \
		ft_memmove.c \
		ft_memccpy.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strjoin.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_substr.c	\
		ft_strtrim.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_trim.c \
		ft_replace.c \
		gnl.c \
		gnl_utils.c \
		ft_split2.c \
		haha.c

OBJS = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) 
	ar rc $(NAME) $(OBJS)
	
clean :
	rm -f $(OBJS) 

fclean :
	rm -f $(OBJS) $(NAME) 
	
re : fclean all

.PHONY: clean fclean all re bonus
