#include "../inc/cub3d.h"

/* check if a pixel of a wall has to be shown in the minimap */
t_bool  is_pix_in_minimap(t_game *game, int x, int y)
{
    t_minimap   *m_map;
    
    m_map = &game->m_map;
    if (x >= m_map->start_l && x <= m_map->end_r
        && y >= m_map->start_up && y <= m_map->end_d)
        return (TRUE);
    return (FALSE);
}

/* check if a tile of the map has to be shown in the minimap */
t_bool  is_tile_in_minimap(t_game *game, int x, int y)
{
    int             map_width;
    double          half_tiles;
    t_double_coo    player;
    t_minimap       *m_map;

    m_map = &game->m_map;
    //player.x = (int)game->pl.pos_x + 0.5;
    //player.y = (int)game->pl.pos_y + 0.5;
    player.x = game->pl.pos_x;
    player.y = game->pl.pos_y;
    map_width = m_map->end_r - m_map->start_l;
    half_tiles = map_width / MAP_TILE_WIDTH / 2;
    if (x > (int)(player.x - half_tiles) && x < player.x + half_tiles
        && y > (int)(player.y - half_tiles) && y < player.y + half_tiles)
        return (TRUE);
    return (FALSE);
}

/* check if a pixel has to belong to the circle representing the player in the minimap */
t_bool	is_inside_circle(t_game *game, int x, int y)
{
    t_minimap       *m_map;

    m_map = &game->m_map;
	float distance = sqrtf(powf(x - m_map->ctr_x, 2.) + powf(y - m_map->ctr_y, 2.));
	if (distance <= MAP_PLAYER_WIDTH / 2)
		return (TRUE); //inside circle
	return (FALSE); //outside circle
}