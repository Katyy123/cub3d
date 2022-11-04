#include "map.h"

t_bool	valid_map(char **map_file, t_pos *pos, t_game *game)
{
    printf("\nIN VALID_MAP FUNCTION\n");
    int i;
    int max_len;
    int y;
    int *len_str;
    int lines_n;

    i = 0;
    max_len = 0;
    y = pos->y;
    lines_n = ft_char_mtx_linecount(&map_file[y]);
    len_str = malloc(sizeof(int) * (lines_n + 1));
    if (!len_str)
        return(error("can't do malloc len_str in valid_map"));
    game->map = malloc(sizeof(char *) * (lines_n + 1));
    if (!game->map)
    {   
        free (len_str);
        return(error("can't do malloc game->map in valid_map"));
    }
    while (map_file[y])
    {
        len_str[i] = ft_strlen(map_file[y]);
        if (len_str[i] > max_len)
            max_len = len_str[i];
        y++;
        i++;
    }
    //fare attenzione, len_str is not null-terminated
    i = 0; 
    y = pos->y;
    while (map_file[y])
    {
        game->map[i] = malloc(sizeof(char) * max_len + 1);
        if (!game->map[i])
        {  
            free (len_str);
            return(error("can't do malloc game->map[i] in valid_map"));
        }
        ft_memcpy((void *)game->map[i], (void *)map_file[y], len_str[i]);
        if (len_str[i] < max_len)
            ft_memset((void *)&game->map[i][len_str[i]], ' ', max_len - len_str[i]);
        game->map[i][max_len] = '\0';
        y++;
        i++;
    }
    game->map[i] = NULL;
    free (len_str);
    i = 0;
    printf("\nThe map:\n");
    while (game->map[i])
    {
        printf("%s\n", game->map[i]);
        i++;
    }
    pos->y = y - 1;
    pos->x = 0 - 1;
//////////////////
    // bool    empty_line;
    // int     last_row;
    // bool    player;
    // int     x;

    // empty_line = 0;
    // last_row = ft_char_mtx_linecount(game->map) - 1;
    // player = 0;
    // x = 0;
    // while (game->map[0][x])
    // {
    //     if (game->map[0][x] != '1' || game->map[0][x] != ' ')
    //         return (error("The map must be closed by walls"))
    //     x++;
    // }
    // y = 1;
    // while (game->map[y] && empty_line == 0)
    // {
    //     if (!game->map[y][0])
    //     {
    //         if (empty_line == 0)
    //             last_row = y - 1;
    //         empty_line = 1;
    //     }
    //     x = 0;
    //     if (game->map[y][0] == ' ')
    //     {
    //         //check if the space is sorrounded at right, up an down
    //     }
    //     while (game->map[y][x])
    //     {
    //         if (game->map[y][x] == ' ')
    //         {
    //             //check if every space is sorrunded by other spaces, '1' or '\0' (manage the case x=0 separately, cause at left it doesn't have anything) 
    //         }
    //         else if (game->map[y][x] == N || game->map[y][x] == S
    //             || game->map[y][x] == E || game->map[y][x] == W)
    //         {
    //             if (empty_line == 1)
    //                 return (error("The map can't have empty lines inside"));
    //             if (player == 1)
    //                 return (error("The map can't have more than 1 player"));
    //             else
    //                 player = 1;
    //             //save player info in t_player struct
    //         } 
    //         else if (game->map[y][x] != '0' && game->map[y][x] != '1')
    //             return (error("Map character not valid"));
    //         else if (empty_line == 1)
    //             return (error("The map can't have empty lines inside"));
    //         x++;
    //     }
    //     y++;
    // }
    // while (game->map[last_row][x])
    // {
    //     while (game->map[last_row][x])
    //     {
    //         if (game->map[last_row][x])

    //         x++;
    //     }
    // }
    
    //manage the last line
	return (TRUE);
}