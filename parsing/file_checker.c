/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:33:53 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/31 19:19:46 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* check the info about textures and colors */
t_bool	valid_info(char *str, t_pos *pos, t_game *game)
{
	printf("\nIN VALID_INFO FUNCTION\n");
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
	else// if (str[pos->x] != '0' && str[pos->x] != '1')
	{
		free (type_id);
		return (error("Wrong type identifier"));
	}
	return (TRUE);
}

/* initialization of the t_textures struct */
void	textures_struct_init(t_game *game)
{
	printf("\nIN TEXTURES_STRUCT_INIT FUNCTION\n");
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	game->textures.f_col = -1;
	game->textures.c_col = -1;
}

/* check if all the info inside the file is valid */
t_bool	valid_file_2(char **map_file, t_game *game, t_pos *pos)
{
	printf("\nIN valid_file_2 FUNCTION\n");
	printf("\npos->y = %d  pos.x = %d\n", pos->y, pos->x);
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
	// else if (map_file[pos->y][pos->x] != '0' && map_file[pos->y][pos->x] != '1')
	// {
	// 	//printf("\n----------pos->y = %d pos->x = %d\n", pos->y, pos->x);
	// 	return (error("The map content is not the last info"));
	// }
	
	return (TRUE);
}

/* check if all the info inside the file is valid */
t_bool	valid_file(char **map_file, t_game *game)
{
	printf("\nIN VALID_FILE FUNCTION\n");
	t_pos pos;
	//t_textures *tex;

	//tex = &game->textures;
	textures_struct_init(game);
	pos.y = 0;
	while (map_file[pos.y])
	{
		//printf("\nIN 1st WHILE OF VALID_FILE FUNCTION\n");
		pos.x = 0;
		//printf("\npos.y = %d\n", pos.y);
		while (map_file[pos.y] && map_file[pos.y][pos.x])
		{
			//printf("\nIN 2nd WHILE OF VALID_FILE FUNCTION\n");
			//printf("pos.y = %d\n", pos.y);
			if (map_file[pos.y][pos.x] == ' ')
			{
				printf("\npos.y = %d  pos.x = %d\n", pos.y, pos.x);
				pos.x++;
				continue;
			}
			if (valid_file_2(map_file, game, &pos) == FALSE)
				return (FALSE);
			pos.x++;
		}
		if (map_file[pos.y])
			pos.y++;
		printf("\n----- pos.y = %d -----\n", pos.y);
	}
	// if (!tex->no || !tex->so || !tex->we || !tex->ea || !tex->f_col || !tex->c_col
	// 	|| !game->map)
	// 	return (error("The file does not contain all the info"));
	if (!game->textures.no || !game->textures.so || !game->textures.we
		|| !game->textures.ea || game->textures.f_col == -1
		|| 	game->textures.c_col == -1 || !game->map)
		return (error("The file does not contain all the info"));
	printf("NO texture: %s\n", game->textures.no);
	printf("SO texture: %s\n", game->textures.so);
	printf("WE texture: %s\n", game->textures.we);
	printf("EA texture: %s\n", game->textures.ea);
	printf("game->textures.f_col = %d\n", game->textures.f_col);
	printf("game->textures.c_col = %d\n", game->textures.c_col);
	//printf("color red code of f: %d\n", game->textures.f_col & (0xFF << 16));
	//printf("color green code of f: %d\n", game->textures.f_col & (0xFF << 8));
	//printf("color blue code of f: %d\n", game->textures.f_col & (0xFF));
	if (game->textures.f_col == 0x00FFFFFF)
		printf("game->textures.f_col == code\n");
	else
		printf("game->textures.f_col != code\n");
	if (game->textures.c_col == 0x0011FE00)
		printf("game->textures.f_col == code\n");
	else
		printf("game->textures.f_col != code\n");
	return (TRUE);
}