/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:06:49 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/31 17:40:18 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../inc/cub3d.h"
# include "../inc/structs.h"
# include <fcntl.h>
# include <unistd.h>
# include "../gnl/get_next_line.h"

typedef struct s_pos
{
	int	x;
	int	y;
} t_pos;

// typedef struct s_file_check_data
// {
// 	int		size_x;
// 	int		size_y;
// 	int		player;
// 	t_bool	border_walls;
// 	t_bool	valid_char;
// 	t_bool	north_texture;
// 	t_bool	south_texture;
// 	t_bool	west_texture;
// 	t_bool	east_texture;
// 	t_bool	f_color;
// 	t_bool	c_color;
// }	t_file_check_data;

/* file_reader.c */
int			valid_arg(int argc, char *file_path);
char		**read_map_file(char *file_path);
int			map_file_parse(char *file_path, t_game *game);

/* file_checker.c */
t_bool		valid_file(char **map_file, t_game *game);

/* texture_checker.c */
int			check_texture_path(char *str, t_pos *pos, t_game *game, char *type_id);

/* color_checker.c */
int			check_color(char *str, t_game *game, t_pos *pos, char *type_id);

/* map_create.c */
t_bool		valid_map(char **map_file, t_pos *pos, t_game *game);

/* map_create_2.c */
int			create_map(char **map_file, t_game *game, int lines_to_remove);

/* map_checker.c */
int			check_map(t_game *game);

#endif