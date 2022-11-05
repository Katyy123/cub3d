# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 18:06:47 by cfiliber          #+#    #+#              #
#    Updated: 2021/12/08 13:50:59 by cfiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isprint.c     ft_putchar_fd.c ft_strlcat.c    ft_substr.c     ft_atoi.c \
	ft_itoa.c       ft_putendl_fd.c ft_strlcpy.c    ft_tolower.c \
	ft_bzero.c      ft_memccpy.c    ft_putnbr_fd.c  ft_strlen.c     ft_toupper.c \
	ft_calloc.c     ft_memchr.c     ft_putstr_fd.c  ft_strmapi.c \
	ft_isalnum.c    ft_memcmp.c     ft_split.c      ft_strncmp.c \
	ft_isalpha.c    ft_memcpy.c     ft_strchr.c     ft_strnstr.c \
	ft_isascii.c    ft_memmove.c    ft_strdup.c     ft_strrchr.c \
	ft_isdigit.c    ft_memset.c     ft_strjoin.c    ft_strtrim.c \
	ft_strend_cmp.c    ft_char_mtx_linecount.c    ft_free_char_mtx.c ft_all_char_same.c \

OBJS = $(SRCS:.c=.o)

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c

BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS)
	ar crs $(NAME) $(OBJS)

.c.o: $(CC) $(CFLAGS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(BONUS)
	ar crs $(NAME) $(OBJS) $(BONUS_OBJS)

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
