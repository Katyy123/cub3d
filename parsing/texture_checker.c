/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:41:30 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/29 18:01:41 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* save the path of the texture inside the t_textures struct */
void	save_textures(char *str, t_game *game, char *type_id)
{
	if (ft_strncmp(type_id, "NO", 2) == 0)
		game->no_tex.path = ft_strdup(str);
	if (ft_strncmp(type_id, "SO", 2) == 0)
		game->so_tex.path = ft_strdup(str);
	if (ft_strncmp(type_id, "WE", 2) == 0)
		game->we_tex.path = ft_strdup(str);
	if (ft_strncmp(type_id, "EA", 2) == 0)
		game->ea_tex.path = ft_strdup(str);
}

/* check the path of the texture */
int	check_texture_path(char *str, t_pos *pos, t_game *game, char *type_id)
{
	int	fd;

	pos->x += 2;
	while (str[pos->x] == ' ')
		pos->x++;
	fd = open(&str[pos->x], O_RDONLY);
	if (fd == -1)
	{
		free (type_id);
		return (-1);
	}
	close(fd);
	save_textures(&str[pos->x], game, type_id);
	pos->x += ft_strlen(&str[pos->x]) - 1;
	free (type_id);
	return (0);
}
