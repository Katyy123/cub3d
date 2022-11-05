#include "parsing.h"

int check_last_line(t_game *game)
{
    printf("\nIN check_last_line FUNCTION\n");
    int x;
    int y;

    x = 0;
    y = game->map_y -1;
    //printf("game->map_y - 1: %d\n", game->map_y - 1);
    while (game->map[y][x])
    {
        if (game->map[y][x] != '1' && game->map[y][x] != ' ')
            return (error_1("----The map must be closed by walls"));
        x++;
    }
    return (0);
}

int check_middle_lines_2(t_game *game, int x, int y)
{
    printf("\nIN check_middle_lines_2 FUNCTION\n");
    if (game->map[y][x] == ' ')
    {
        printf("----------y = %d, x = %d\n", y, x);
        if (space_closed_by_walls(game, y, x) == FALSE)
            return (error_1("____The map must be closed by walls"));
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
    return (0);
}

int check_middle_lines(t_game *game)
{
    printf("\nIN check_middle_lines FUNCTION\n");
    int x;
    int y;
    
    y = 1;
    while (game->map[y] && game->map[y + 1])
    {
        x = 0;
        if (check_first_elem(game, y) == -1)
            return (-1);
        if (check_empty_line(game, y) == -1)
            return (-1);
        while (game->map[y][x])
        {
            if (check_middle_lines_2(game, x, y) == -1)
                return (-1);
            x++;
        }
        y++;
    }
    return (0);
}

int check_first_line(t_game *game)
{
    printf("\nIN check_first_line FUNCTION\n");
    int x;
    
    x = 0;
    while (game->map[0][x])
    {
        if (game->map[0][x] != '1' && game->map[0][x] != ' ')
            return (error_1("!!!!The map must be closed by walls"));
        x++;
    }
    return (0);
}

int check_map(t_game *game)
{
    printf("\nIN check_map FUNCTION\n");   
    player_struct_init(&(game->pl));

    if (check_first_line(game) == -1)
        return (-1);
    if (check_middle_lines(game) == -1)
        return (-1); 
    if (check_last_line(game) == -1)
        return (-1);
    if (game->pl.pos_x == -1)
        return (error_1("The map must have a player"));
    return (0);
}