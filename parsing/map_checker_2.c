/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:41:01 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/13 10:27:34 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* save player data in the t_player struct */
void	save_player_data(t_player *player, int x, int y, char dir)
{
<<<<<<< HEAD
    //printf("\nIN save_player_data FUNCTION\n");
    player->pos_x = x;
    player->pos_y = y;
    if (dir == 'E')
        player->pov = 0;
    else if (dir == 'S')
         player->pov = 3.14 / 2;
    else if (dir == 'W')
        player->pov = 3.14;
    else if (dir == 'N')
        player->pov = 3 * 3.14 / 2;
=======
	player->pos_x = x;
	player->pos_y = y;
	if (dir == 'E')
		player->pov = 0;
	else if (dir == 'S')
		player->pov = 3.14 / 2;
	else if (dir == 'W')
		player->pov = 3.14;
	else if (dir == 'N')
		player->pov = 3 * 3.14 / 2;
>>>>>>> 6e6f7ce01791874dbe401aa6ac3b54836b4b1ce0
}

/* check if a space is surrounded (up, down, left, right)
by an other space, a 1 or a \0 */
t_bool	space_closed_by_walls(t_game *game, int y, int x)
{
	if (game->map[y][x + 1] != ' ' && game->map[y][x + 1] != '1'
		&& game->map[y][x + 1] != '\0')
		return (FALSE);
	if (game->map[y - 1][x] != ' ' && game->map[y - 1][x] != '1')
		return (FALSE);
	if (game->map[y + 1][x] != ' ' && game->map[y + 1][x] != '1')
		return (FALSE);
	if (x != 0)
	{
		if (game->map[y][x - 1] != ' ' && game->map[y][x - 1] != '1')
			return (FALSE);
	}
	return (TRUE);
}

/* check if there is an empty line (or a line containing only spaces)
inside the map.
In that case it considers the map as it ends before that line */
int	check_empty_line(t_game *game, int y)
{
	if (ft_all_char_same(game->map[y], ' '))
		return (error_1("The map content is not the last info"));
	return (0);
}

/* check the first element of every line from the 2nd line
till the second to last */
int	check_first_elem(t_game *game, int y)
{
	if (game->map[y][0] != '1' && game->map[y][0] != ' ')
		return (error_1("The map must be closed by walls"));
	return (0);
}

/* initialize the t_player struct */
void	player_struct_init(t_player *player)
{
	player->pos_x = -1;
	player->pos_y = -1;
	player->view = 3.14159 / 4.0;
	player->pos_x = -1;
}
