#include "map.h"

t_bool	valid_map(char **map_file, /*t_pos *pos, */t_game *game)
{
    printf("\nIN VALID_MAP FUNCTION\n");
    game->map = map_file;//messo solo per non avere map==NULL
    //aumentare pos_y e pos_x
	return (TRUE);
}