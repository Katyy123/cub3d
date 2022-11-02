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

t_bool	valid_info(char *str, t_pos *pos, t_game *game)
{
	char *type_id;

	type_id = ft_substr(&str[pos->x], 0, 2);
	//printf("str[pos->x]: %c\n", str[pos->x]);
	//printf("type_id = %s\n", type_id);
	if (ft_strncmp(type_id, "NO", 2) == 0
		|| ft_strncmp(type_id, "SO", 2) == 0
		|| ft_strncmp(type_id, "WE", 2) == 0
		|| ft_strncmp(type_id, "EA", 2) == 0)
	{
		if (check_texture_path(str, pos, game, type_id) == -1)
			return (error("Wrong or missing texture path"));
	}
	else if (ft_strncmp(type_id, "F", 1) == 0
		|| ft_strncmp(type_id, "C", 1) == 0)
	{
		if (check_color(str, game, pos, type_id) == -1)
			return (error("Wrong or missing color code"));
	}
	else// if (str[pos->x] != '0' && str[pos->x] != '1')
	{
		free (type_id);
		return (error("Wrong type identifier"));
	}
	// else
	// 	free (type_id);
	return (TRUE);
}

void	textures_struct_init(t_game *game)
{
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->textures.f_col = -1;
	game->textures.c_col = -1;
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
		//printf("***pos.x = %d\n", pos.x);
		//printf("***map_file[pos.y][pos.x] = %c\n", map_file[pos.y][pos.x]);
		while (map_file[pos.y][pos.x])
		{
			//printf("__pos.y = %d\n", pos.y);
			printf("__pos.x = %d\n", pos.x);
			if (map_file[pos.y][pos.x] == ' ')
			{
				pos.x++;
				continue;
			}
			if (map_file[pos.y][pos.x] != 0 && map_file[pos.y][pos.x] != 1)
			{
				if (valid_info(map_file[pos.y], &pos, game) == FALSE)
					return (FALSE);
			}
			else
			{
				if (valid_map(/*map_file, pos, */game) == FALSE)
					return (FALSE);	
			}
			pos.x++;
		}
		pos.y++;
	}
	printf("NO texture: %s\n", game->textures.no);
	printf("SO texture: %s\n", game->textures.so);
	printf("WE texture: %s\n", game->textures.we);
	printf("EA texture: %s\n", game->textures.ea);
	printf("----game->textures.f_col = %d\n", game->textures.f_col);
	printf("----game->textures.c_col = %d\n", game->textures.c_col);
	//printf("color red code of f: %d\n", game->textures.f_col & (0xFF << 16));
	//printf("color green code of f: %d\n", game->textures.f_col & (0xFF << 8));
	//printf("color blue code of f: %d\n", game->textures.f_col & (0xFF));
	if (game->textures.f_col == 0x00FF0001)
		printf("---game->textures.f_col == code\n");
	else
		printf("---game->textures.f_col != code\n");
	return (TRUE);
}