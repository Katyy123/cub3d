#include "parsing.h"

// int check_map(t_game *game)
//     bool    empty_line;
//     int     last_row;
//     bool    player;
//     int     x;

//     empty_line = 0;
//     last_row = ft_char_mtx_linecount(game->map) - 1;
//     player = 0;
//     x = 0;
//     while (game->map[0][x])
//     {
//         if (game->map[0][x] != '1' || game->map[0][x] != ' ')
//             return (error("The map must be closed by walls"))
//         x++;
//     }
//     y = 1;
//     while (game->map[y] && empty_line == 0)
//     {
//         if (!game->map[y][0])
//         {
//             if (empty_line == 0)
//                 last_row = y - 1;
//             empty_line = 1;
//         }
//         x = 0;
//         if (game->map[y][0] == ' ')
//         {
//             //check if the space is sorrounded at right, up an down
//             if (game->map[y][1] !)
//         }
//         while (game->map[y][x])
//         {
//             if (game->map[y][x] == ' ')
//             {
//                 //check if every space is sorrunded by other spaces, '1' or '\0' (manage the case x=0 separately, cause at left it doesn't have anything) 
//             }
//             else if (game->map[y][x] == N || game->map[y][x] == S
//                 || game->map[y][x] == E || game->map[y][x] == W)
//             {
//                 if (empty_line == 1)
//                     return (error("The map can't have empty lines inside"));
//                 if (player == 1)
//                     return (error("The map can't have more than 1 player"));
//                 else
//                     player = 1;
//                 //save player info in t_player struct
//             } 
//             else if (game->map[y][x] != '0' && game->map[y][x] != '1')
//                 return (error("Map character not valid"));
//             else if (empty_line == 1)
//                 return (error("The map can't have empty lines inside"));
//             x++;
//         }
//         y++;
//     }
//     while (game->map[last_row][x])
//     {
//         while (game->map[last_row][x])
//         {
//             if (game->map[last_row][x])

//             x++;
//         }
//     }
    
//     //manage the last line
// 	return (TRUE);
// }