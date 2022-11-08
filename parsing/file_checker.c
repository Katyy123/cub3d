/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:33:53 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/08 20:10:10 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* check the info about textures and colors */
t_bool	valid_info(char *str, t_pos *pos, t_game *game)
{
	//printf("\nIN VALID_INFO FUNCTION\n");
	char *type_id;

	type_id = ft_substr(&str[pos->x], 0, 2);
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
	else
	{
		free (type_id);
		return (error("Wrong type identifier"));
	}
	return (TRUE);
}

/* initialization of the t_textures struct */
void	textures_struct_init(t_game *game)
{
	//printf("\nIN TEXTURES_STRUCT_INIT FUNCTION\n");
	game->no_tex.path = NULL;
	game->so_tex.path = NULL;
	game->we_tex.path = NULL;
	game->ea_tex.path = NULL;
	game->col.f_col = -1;
	game->col.c_col = -1;
}

/* check if all the info inside the file is valid */
t_bool	valid_file_2(char **map_file, t_game *game, t_pos *pos)
{
	//printf("\nIN valid_file_2 FUNCTION\n");
	//printf("\npos->y = %d  pos.x = %d\n", pos->y, pos->x);
	if (map_file[pos->y][pos->x] != '0' && map_file[pos->y][pos->x] != '1'
		&& !game->map)
	{
		if (valid_info(map_file[pos->y], pos, game) == FALSE)
			return (FALSE);
	}
	else if (!game->map)
	{
		if (valid_map(map_file, pos, game) == FALSE)
			return (FALSE);	
	}
	
	return (TRUE);
}

/* check if all the info inside the file is valid */
t_bool	valid_file(char **map_file, t_game *game)
{
	//printf("\nIN VALID_FILE FUNCTION\n");
	t_pos pos;

	textures_struct_init(game);
	pos.y = 0;
	while (map_file[pos.y])
	{
		pos.x = 0;
		//printf("\npos.y = %d\n", pos.y);
		while (map_file[pos.y] && map_file[pos.y][pos.x])
		{
			//printf("pos.y = %d\n", pos.y);
			if (map_file[pos.y][pos.x] == ' ')
			{
				//printf("\npos.y = %d  pos.x = %d\n", pos.y, pos.x);
				pos.x++;
				continue;
			}
			if (valid_file_2(map_file, game, &pos) == FALSE)
				return (FALSE);
			pos.x++;
			//printf("\npos.y = %d  pos->x = %d\n", pos.y, pos.x);
		}
		if (map_file[pos.y])
			pos.y++;
		//printf("\n----- pos.y = %d -----\n", pos.y);
	}
	if (!game->no_tex.path || !game->so_tex.path || !game->we_tex.path
		|| !game->ea_tex.path || game->col.f_col == -1
		|| 	game->col.c_col == -1 || !game->map)
		return (error("The file does not contain all the info"));
	printf("NO texture: %s\n", game->no_tex.path);
	printf("SO texture: %s\n", game->so_tex.path);
	printf("WE texture: %s\n", game->we_tex.path);
	printf("EA texture: %s\n\n", game->ea_tex.path);
	//printf("floor color = %d\n", game->col.f_col);
	//printf("ceiling color = %d\n", game->col.c_col);
	//printf("color red code of floor: %d\n", game->col.f_col & (0xFF << 16));
	//printf("color green code of floor: %d\n", game->col.f_col & (0xFF << 8));
	//printf("color blue code of floor: %d\n", game->col.f_col & (0xFF));
	if (game->col.f_col == 0x00FFFFFF)
		printf("floor color == color in the file\n");
	else
		printf("floor color != color int the file\n");
	if (game->col.c_col == 0x0011FE00)
		printf("ceiling color == color in the file\n\n");
	else
		printf("ceiling color != color in the file\n\n");
	printf("player.pos_x = %f\n", game->pl.pos_x);
    printf("player.pos_y = %f\n", game->pl.pos_y);
    printf("player.view = %f\n", game->pl.view);
    printf("player.pov = %f\n", game->pl.pov);
	return (TRUE);
}