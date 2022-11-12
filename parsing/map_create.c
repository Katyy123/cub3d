/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:41:18 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/12 19:19:20 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* find the end of the map excluding final emty lines
or lines containing only spaces */
int	find_lines_to_remove(char **map_file)
{
	int	last_line;
	int	i;

	i = 0;
	last_line = ft_char_mtx_linecount(map_file) - 1;
	while (map_file[last_line])
	{
		if (!map_file[last_line][0]
			|| ft_all_char_same(map_file[last_line], ' '))
		{
			last_line--;
			i++;
			continue ;
		}
		return (i);
	}
	return (i);
}

/* call the functions that create the map and that check if it is valid */
t_bool	valid_map(char **map_file, t_pos *pos, t_game *game)
{
	int	i;
	int	lines_to_remove;

	lines_to_remove = find_lines_to_remove(map_file);
	if (create_map(&map_file[pos->y], game, lines_to_remove) == -1)
		return (FALSE);
	i = 0;
	printf("The map:\n");
	while (game->map[i])
	{
		printf("%s$\n", game->map[i]);
		i++;
	}
	printf("--end map--\n\n");
	if (check_map(game) == -1)
		return (FALSE);
	pos->y += game->map_y;
	pos->x = 0 - 1;
	return (TRUE);
}
