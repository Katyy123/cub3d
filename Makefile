# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 16:37:56 by cfiliber          #+#    #+#              #
#    Updated: 2022/10/31 14:18:16 by cfiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

LIB_PATH = ./libft/
LIB = $(LIB_PATH)libft.a

SRCS = $(MAIN_SRC) $(SRC_GNL) $(SRC_MAP) $(SRC_GAME)

MAIN_SRC = main.c errors.c

GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix gnl/, $(GNL))

MAP = map_reader.c map_checker.c
SRC_MAP = $(addprefix map/, $(MAP))

GAME = 
SRC_GAME = $(addprefix game/, $(GAME))

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I libft -Imlx -fsanitize=address

GREEN = '\x1b[32m'
YELLOW = '\x1b[33m'
RED = '\x1b[31m'
MAGENTA = '\x1b[35m'
CYAN = '\x1b[36m'
GRAY = '\x1b[2;37m'
CURSIVE = '\x1b[3m'
RESET = '\x1b[0m'

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: subsystem $(NAME)

subsystem:
	make all -C $(LIB_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)
	@echo $(GREEN)$(CURSIVE)"\nAll files have been compiled"$(RESET)
	@echo $(MAGENTA)$(CURSIVE)"\nTo start the game, type ./cub3d and map name.\nFor example: ./cub3d maps/test1.cub\n"$(RESET)

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
