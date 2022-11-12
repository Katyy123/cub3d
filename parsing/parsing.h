/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:06:49 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/12 19:29:42 by cfiliber         ###   ########.fr       */
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
}	t_pos;

/* file_reader.c */
int		valid_arg(int argc, char *file_path);
int		file_linecount(char *file);
char	**read_map_file(char *file_path);
int		map_file_parse(char *file_path, t_game *game);

/* file_checker.c */
t_bool	valid_info(char *str, t_pos *pos, t_game *game);
void	textures_struct_init(t_game *game);
t_bool	valid_file_2(char **map_file, t_game *game, t_pos *pos);
t_bool	all_info(t_game *game);
t_bool	valid_file(char **map_file, t_game *game);

/* texture_checker.c */
int		check_texture_path(char *str, t_pos *pos, t_game *game, char *type_id);

/* color_checker.c */
void	save_color(int *col_arr, t_game *game, char *type_id);
int		free_stuff(char *type_id, char **color_mtx, int *color_arr);
int		check_color_param(char *type_id, char **color_mtx, int *color_arr);
int		check_color(char *str, t_game *game, t_pos *pos, char *type_id);

/* map_create.c */
int		find_lines_to_remove(char **map_file);
t_bool	valid_map(char **map_file, t_pos *pos, t_game *game);

/* map_create_2.c */
int		alloc_map_strings(t_game *game, int max_len, int *len_str, int i);
int		find_max_strlen(char **map_file, int *len_str, int lines_to_remove);
int		*alloc_lenstr_map(char **map_file, t_game *game, int lines_to_remove);
int		create_map(char **map_file, t_game *game, int lines_to_remove);

/* map_checker.c */
int		check_last_line(t_game *game);
int		check_middle_lines_2(t_game *game, int x, int y);
int		check_middle_lines(t_game *game);
int		check_first_line(t_game *game);
int		check_map(t_game *game);

/* map_checker_2.c */
void	save_player_data(t_player *player, int x, int y, char dir);
t_bool	space_closed_by_walls(t_game *game, int y, int x);
int		check_empty_line(t_game *game, int y);
int		check_first_elem(t_game *game, int y);
void	player_struct_init(t_player *player);

#endif