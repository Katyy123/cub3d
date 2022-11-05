#include "parsing.h"

/* find the end of the map excluding final emty lines or lines containing only spaces */
int find_lines_to_remove(char **map_file)
{
    printf("\nIN find_lines_to_remove FUNCTION\n");
    int last_line;
    int i;

    i = 0;
    last_line = ft_char_mtx_linecount(map_file) - 1;
    while (map_file[last_line])
    {
        if (!map_file[last_line][0]
            || ft_all_char_same(map_file[last_line], ' '))
        {
            last_line--;
            i++;
            continue;
        }
        return (i);
    }
    return (i);
}

/* call the functions that create the map and that check if it is valid */
t_bool	valid_map(char **map_file, t_pos *pos, t_game *game)
{
    printf("\nIN VALID_MAP FUNCTION\n");
    int i;
    int lines_to_remove;

    lines_to_remove = find_lines_to_remove(map_file);
    if (create_map(&map_file[pos->y], game, lines_to_remove) == -1)
        return (FALSE);
    i = 0;
    printf("The map:\n");
    while (game->map[i])
    {
        printf("%s\n", game->map[i]);
        i++;
    }
    printf("--end map--\n");
    int y = 0;
    while (game->map[y])
    {
        int x = 0;
        while (game->map[y][x])
        {
            printf("game->map[%d][%d] : %c$\n", y, x, game->map[y][x]);
            x++;
        }
        if (!game->map[y][x])
            printf("game->map[%d][%d] : NULL\n", y, x);
        y++;
    }
    if (check_map(game) == -1)
        return (FALSE);//eventualmente scrivere qui error("The map is not valid")
    pos->y += game->map_y;
    pos->x = 0 - 1;
    return (TRUE);
}