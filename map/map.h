/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:06:49 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/31 17:40:18 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../inc/cub3d.h"
# include "../inc/structs.h"
# include <fcntl.h>
# include <unistd.h>
# include "../gnl/get_next_line.h"

typedef struct s_file_check_data
{
	int		size_x;
	int		size_y;
	int		player;
	t_bool	border_walls;
	t_bool	valid_char;
	t_bool	north_texture;
	t_bool	south_texture;
	t_bool	west_texture;
	t_bool	east_texture;
	t_bool	f_color;
	t_bool	c_color;
}	t_file_check_data;

/* map_reader.c */
int					valid_arg(int argc, char *file_path);
char				**read_map_file(char *file_path);
char				**map_file_parse(char *file_path, t_game *game);

/* map_checker.c */
t_bool				valid_file(char **map_file, t_game *game);

#endif