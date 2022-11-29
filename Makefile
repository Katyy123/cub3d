# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 16:37:56 by cfiliber          #+#    #+#              #
#    Updated: 2022/11/29 20:27:53 by cfiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

NAME_BONUS	= cub3D_bonus

LIB_PATH = ./libft/
LIB = $(LIB_PATH)libft.a

SRCS = $(MAIN_SRC) $(SRC_GNL) $(SRC_PARSING) $(SRC_GAME)

SRCS_BONUS = $(MAIN_SRC) $(SRC_GNL) $(SRC_PARSING) $(SRC_GAME_BONUS)

MAIN_SRC = main.c errors.c

GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix gnl/, $(GNL))

PARSING = file_reader.c file_checker.c texture_checker.c color_checker.c \
		 map_create.c map_create_2.c map_checker.c map_checker_2.c
SRC_PARSING = $(addprefix parsing/, $(PARSING))

GAME = cub3d.c end_program.c minimap_background.c minimap_utils.c minimap.c mouse_input.c \
		update_pos.c move_utils.c raycast_utils.c init.c text_utils.c text_utils2.c mlx.c
SRC_GAME = $(addprefix game/, $(GAME))

GAME_BONUS = cub3d_bonus.c end_program_bonus.c minimap_background_bonus.c minimap_utils_bonus.c minimap_bonus.c mouse_input_bonus.c \
		update_pos_bonus.c move_utils_bonus.c raycast_utils_bonus.c init_bonus.c text_utils_bonus.c text_utils2_bonus.c mlx_bonus.c
SRC_GAME_BONUS = $(addprefix game_bonus/, $(GAME_BONUS))

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I libft -Imlx #-fsanitize=address

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
	@make all -C $(LIB_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) $(LIB)
	@echo $(GREEN)$(CURSIVE)"\nAll files have been compiled"$(RESET)
	@echo $(MAGENTA)$(CURSIVE)"\nTo start the game, type ./cub3d and map name.\nFor example: ./cub3d maps/test1.cub\n"$(RESET)

bonus: fclean subsystem $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS) $(OBJS_BONUS) $(LIB)
	@echo $(GREEN)$(CURSIVE)"\nAll files have been compiled"$(RESET)
	@echo $(MAGENTA)$(CURSIVE)"\nTo start the game, type ./cub3d and map name.\nFor example: ./cub3d maps/test1.cub\n"$(RESET)

clean:
	@make clean -C $(LIB_PATH)
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
