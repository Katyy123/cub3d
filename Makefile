# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 16:37:56 by cfiliber          #+#    #+#              #
#    Updated: 2022/10/30 14:07:10 by cfiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRCS	= cub3d.c \
		

FLGS	= gcc -Werror -Wall -Wextra 
LINKS = -lmlx -framework OpenGL -framework AppKit


RM		= rm -f

all:	$(NAME) $(SRCS)

$(NAME): $(SRCS)
	$(FLGS) $(LINKS) $(SRCS) -o $(NAME)
#	make -C lib
# $(FLGS)  -lmlx -framework OpenGL -framework AppKit -Ofast -g3 -flto -march=native -O3 -ffast-math -msse4.2 -mtune=intel lib/libmlx.a $(SRCS) -o $(NAME)

clean: 
	$(RM) -fr $(NAME)

fclean: clean
	make clean -C lib
	$(RM) -fr img/guns/g1 img/guns/g2 img/guns/g3 img/guns/g4 img/guns/g5 img/guns/g6 img/guns/g7 img/guns/g8 img/guns/g9 img/enemies/attack_1 img/enemies/attack_2 img/enemies/attack_3 img/enemies/hit img/enemies/death img/enemies/walk img/enemies/run
re: fclean all

.PHONY: clean fclean all re