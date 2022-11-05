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

int check_first_elem(t_game *game, int y)
{
    if (!game->map[y][0])
        return (error_1("The map content is not the last info"));
    else if (game->map[y][0] != 1)
        return (error_1("The map must be closed by walls"));
    return (0);
}

void    player_struct_init(t_player *player)
{
    printf("\nIN player_struct_init FUNCTION\n");
    player->pos_x = -1;
    player->pos_y = -1;
    player->view = 3.14/2;
    player->pos_x = -1;
}