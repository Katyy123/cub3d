#include "parsing.h"

void    save_player_data(t_player *player, int x, int y, char dir)
{
    printf("\nIN save_player_data FUNCTION\n");
    player->pos_x = x;
    player->pos_y = y;
    player->view = 3.14;
    if (dir == 'E')
        player->pov = 0;
    else if (dir == 'S')
        player->pov = 3.14 / 2;
    else if (dir == 'W')
        player->pov = 3.14;
    else if (dir == 'N')
        player->pov = 3 * 3.14 / 2;
    printf("player->pos_x = %f\n", player->pos_x);
    printf("player->pos_y = %f\n", player->pos_y);
    printf("player->view = %f\n", player->view);
    printf("player->pov = %f\n", player->pov);
}

t_bool  space_closed_by_walls(t_game *game, int y, int x)
{
    printf("\nIN space_closed_by_walls FUNCTION\n");
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

void    player_struct_init(t_player *player)
{
    printf("\nIN player_struct_init FUNCTION\n");
    player->pos_x = -1;
    player->pos_y = -1;
    player->view = 3.14/2;
    player->pos_x = -1;
}

int check_map(t_game *game)
{
    printf("\nIN check_map FUNCTION\n");
    int x;
    int y;    

    player_struct_init(&(game->pl));
    x = 0;
    while (game->map[0][x])
    {
        if (game->map[0][x] != '1' && game->map[0][x] != ' ')
            return (error_1("The map must be closed by walls"));
        x++;
    }
    y = 1;
    while (game->map[y + 1])// && empty_line == 0)
    {
        x = 0;
        if (!game->map[y][x])
            return (error_1("The map content is not the last info"));
        else if (game->map[y][x] != 1)
            return (error_1("The map must be closed by walls"));
        while (game->map[y][x])
        {
            if (game->map[y][x] == ' ')
            {
                //check if every space is sorrounded by other spaces, '1' or '\0' (manage the case x=0 separately, cause at left it doesn't have anything) 
                if (space_closed_by_walls(game, y, x) == FALSE)
                    return (error_1("The map must be closed by walls"));
            }
            else if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
                || game->map[y][x] == 'E' || game->map[y][x] == 'W')
            {
                if (game->pl.pos_x != -1)
                    return (error_1("The map can't have more than 1 player"));
                save_player_data(&(game->pl), x, y, game->map[y][x]);
            } 
            else if (game->map[y][x] != '0' && game->map[y][x] != '1')
                return (error_1("Map character not valid"));
            x++;
        }
        y++;
    }
    while (game->map[y][x])
    {
        if (game->map[0][x] != '1' && game->map[0][x] != ' ')
            return (error_1("The map must be closed by walls"));
        x++;
    }
	return (0);
}