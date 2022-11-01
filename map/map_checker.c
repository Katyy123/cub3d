/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:33:53 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/31 19:19:46 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_bool	valid_map(/*char **map_file, t_pos *pos, */t_game *game)
{
	if (!game->textures.no || !game->textures.so
		|| !game->textures.we || !game->textures.ea)
		return (error("The map content is not the last info"));
	return (TRUE);
}

void save_textures(char *str, t_game * game, char *type_id)
{
	if (ft_strncmp(type_id, "NO", 2) == 0)
		game->textures.no = str;
	if (ft_strncmp(type_id, "SO", 2) == 0)
		game->textures.so = str;
	if (ft_strncmp(type_id, "WE", 2) == 0)
		game->textures.we = str;
	if (ft_strncmp(type_id, "EA", 2) == 0)
		game->textures.ea = str;
	printf("NO texture: %s\n", game->textures.no);
	printf("SO texture: %s\n", game->textures.so);
	printf("WE texture: %s\n", game->textures.we);
	printf("EA texture: %s\n", game->textures.ea);
}

int	check_texture_path(char *str, t_pos *pos, t_game *game, char *type_id)
{
	int fd;
	//int i;

	//i = 0;
	pos->x += 2;
	while (str[pos->x] == ' ')
		pos->x++;
	printf("&str[pos->x]: %s\n", &str[pos->x]);
	fd = open(&str[pos->x], O_RDONLY);
	if (fd == -1)
	{
		free (type_id);
		return (-1);
	}
	close(fd);
	save_textures(&str[pos->x], game, type_id);
	pos->x += ft_strlen(&str[pos->x]) - 1;//-1 perché poi in valid_file faccio pos.x++
	free (type_id);
	return (0);
}

int	check_color(/*char *str, t_game *game, */t_pos *pos, char *type_id)
{
	pos->x += 2;
	free (type_id);
	return 0;
}

t_bool	valid_info(char *str, t_pos *pos, t_game *game)
{
	char *type_id;

	type_id = ft_substr(&str[pos->x], 0, 2);
	printf("str[pos->x]: %c\n", str[pos->x]);
	printf("type_id = %s\n", type_id);
	if (ft_strncmp(type_id, "NO", 2) == 0
		|| ft_strncmp(type_id, "SO", 2) == 0
		|| ft_strncmp(type_id, "WE", 2) == 0
		|| ft_strncmp(type_id, "EA", 2) == 0)
	{
		if (check_texture_path(str, pos, game, type_id) == -1)
			return (error("Wrong or missing texture path"));
	}
	else if (ft_strncmp(type_id, "F ", 2) == 0
		|| ft_strncmp(type_id, "C ", 2) == 0)
	{
		if (check_color(/*str, game, */pos, type_id) == -1)
			return (error("Wrong color"));
	}
	else if (str[pos->x] != '0' && str[pos->x] != '1')
	{
		free (type_id);
		return (error("Wrong type identifier"));
	}
	return (TRUE);
}

t_bool	valid_file_2(char **map_file, t_pos *pos, t_game *game)
{
	if (valid_info(map_file[pos->y], pos, game) == FALSE)
					return (FALSE);
	printf("pos.y = %d\n", pos->y);
	printf("pos.x = %d\n", pos->x);
	if (map_file[pos->y][pos->x] == '0' || map_file[pos->y][pos->x] == '1')
	{
		if (valid_map(/*map_file, pos, */game) == FALSE)
			return (FALSE);	
	}
	return (TRUE);	
}

void	textures_struct_init(t_game *game)
{
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
}

t_bool	valid_file(char **map_file, t_game *game)
{
	t_pos pos;

	pos.y = 0;
	textures_struct_init(game);
	while (map_file[pos.y])
	{
		pos.x = 0;
		printf("***pos.y = %d\n", pos.y);
		printf("***pos.x = %d\n", pos.x);
		printf("***map_file[pos.y][pos.x] = %c\n", map_file[pos.y][pos.x]);
		while (map_file[pos.y][pos.x])
		{
			printf("__pos.y = %d\n", pos.y);
			printf("__pos.x = %d\n", pos.x);
			if (map_file[pos.y][pos.x] == ' ')
			{
				pos.x++;
				continue;
			}
			if (valid_file_2(map_file, &pos, game) == FALSE)
				return (FALSE);
			pos.x++;
		}
		pos.y++;
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