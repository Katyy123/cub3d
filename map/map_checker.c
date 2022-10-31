/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:33:53 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/31 15:45:24 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_bool	valid_map()
{
	if (!game->textures.no || !game->textures.so
					|| !game->textures.we || !game->textures.ea)
					return (error("The map content is not the last info"));
}

void save_textures()

int	check_path(char *str, unsigned int pos, char *texture_elem, char *type_id)
{
	int fd;

	free (type_id);
	while (str[pos] == ' ')
		pos++;
	fd = open(&str[pos], O_RDONLY);
	if (!fd)
		return (-1);
	close(fd);
	save_textures(str, )
	//texture_elem = &str[pos];
	return (0);
}

t_bool	valid_texture_info(char *str, t_game *game)
{
	
}

t_bool	valid_info(char *file_str, unsigned int pos, t_game *game)
{
	char *type_id;

	type_id = ft_substr(file_str, pos, 2);
	// if (ft_strncmp(type_id, "NO", 2) != 0
	// 	&& ft_strncmp(type_id, "SO", 2) != 0
	// 	&& ft_strncmp(type_id, "WE", 2) != 0
	// 	&& ft_strncmp(type_id, "EA", 2) != 0
	// 	&& ft_strncmp(type_id, "F ", 2) != 0
	// 	&& ft_strncmp(type_id, "C ", 2) != 0
	// 	&& file_str[pos] != 0
	// 	&& file_str[pos] != 1)
	// 	return (error("Wrong type identifier"));
	// if (file_str[pos] != 0 && file_str[pos] != 1)
	// 	while (ft_strncmp(file_str[pos], ))

	
	if (ft_strncmp(type_id, "NO", 2) == 0
		|| ft_strncmp(type_id, "SO", 2) == 0
		|| ft_strncmp(type_id, "WE", 2) == 0
		|| ft_strncmp(type_id, "EA", 2) == 0)
	{
		if (check_path(file_str, pos + 2, game, type_id) == FALSE)
			return (error("Wrong texture path"));
	}
	if (ft_strncmp(type_id, "NO", 2) == 0)
	{
		if (check_path(file_str, pos + 2, game->textures.no, type_id) == -1)
			return (error("Wrong NO texture path"));
	}
	else if (ft_strncmp(type_id, "SO", 2) == 0)
	{
		if (check_path(file_str, pos + 2, game->textures.no, type_id) == -1)
			return (error("Wrong SO texture path"));
	}
	else if (ft_strncmp(type_id, "WE", 2) == 0)
	{
		if (check_path(file_str, pos + 2, game->textures.no, type_id) == -1)
			return (error("Wrong WE texture path"));
	}
	else if (ft_strncmp(type_id, "EA", 2) == 0)
	{
		if (check_path(file_str, pos + 2, game->textures.no, type_id) == -1)
			return (error("Wrong EA texture path"));
	}
	else// if (file_str[pos] != 0 && file_str[pos] != 1)
		return (error("Wrong type identifier"));
}

t_bool	valid_file(char **map_file, t_game *game)
{
	int	x;
	int	y;
	
	y = 0;
	while (map_file[y])
	{
		x = 0;
		while (map_file[y][x])
		{
			if (map_file[y][x] == ' ')
			{
				x++;
				continue;
			}
			else if (map_file[y][x] != 0 && map_file[y][x] != 1)
			{
				if (valid_info(map_file[y], x, game) == FALSE)
					return (FALSE);
			}
			else
			{
				if (valid_map(&map_file[y], x, game) == FALSE)
					return (FALSE);	
			}	
		}
		y++;
	}
	return (TRUE);
}

// t_file_check_data	map_check_init(char **map)
// {
// 	t_file_check_data	data;

// 	data.size_x = ft_strlen(map[0]);
// 	data.size_y = ft_char_mtx_linecount(map);
// 	data.player = 0;
// 	data.border_walls = TRUE;
// 	data.valid_char = TRUE;
// 	return (data);
// }

// t_bool	valid_map(char **map)
// {
// 	t_file_check_data	data;
// 	t_bool				valid;
// 	int					x;
// 	int					y;

// 	valid = TRUE;
// 	y = 0;
// 	data = map_check_init(map);
// 	while (map[y])
// 	{
// 		is_rectangular(map[y], &data);
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			is_valid_char(map[y][x], &data);
// 			check_border(map[y][x], &data, x, y);
// 			count_chars(&data, map[y][x]);
// 			x++;
// 		}
// 		y++;
// 	}
// 	check_map_size(x, y);
// 	valid = check_map_errors(data);
// 	return (valid);
// }