#include "map.h"

t_bool	valid_map(/*char **map_file, t_pos *pos, */t_game *game)
{
	if (!game->textures.no || !game->textures.so || !game->textures.we
		|| !game->textures.ea || game->textures.f_col == 0x00000000
		|| 	game->textures.c_col == 0x00000000)
		return (error("The map content is not the last info"));
	return (TRUE);
}