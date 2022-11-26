#include "../inc/cub3d.h"

/* initialize t_minimap struct */
void    init_minimap(t_game *game)
{
    t_minimap   *m_map;

    m_map = &game->m_map;
    m_map->bd_width = W / 300;
    m_map->tile_width = W / 100;
    m_map->pl_width = W / 150;
    m_map->dist_win = 20;
    m_map->bd_start_l = 4 * W / 5;
    m_map->bd_start_up = H - (W - m_map->bd_start_l);
    m_map->bd_end_d = H - m_map->dist_win;
    m_map->bd_end_r = W - m_map->dist_win;
    m_map->start_up = m_map->bd_start_up + m_map->bd_width;
    m_map->start_l = m_map->bd_start_l + m_map->bd_width;
    m_map->end_d = m_map->bd_end_d - m_map->bd_width;
    m_map->end_r = m_map->bd_end_r - m_map->bd_width;
    m_map->ctr_x = (m_map->start_l + (W - m_map->dist_win)) / 2;
    m_map->ctr_y = (m_map->start_up + (H - m_map->dist_win)) / 2;
}

/* draw a single wall in the minimap */
void    draw_wall(t_game *game, int tile_x, int tile_y)
{
    int             x;
    int             y;
    t_double_coo    dist_pl_tile_pix;
    t_screen        *screen;
    t_minimap       *m_map;

    screen = &game->screen;
    m_map = &game->m_map;
    dist_pl_tile_pix.x = (game->pl.pos_x - tile_x) * m_map->tile_width;
    dist_pl_tile_pix.y = (game->pl.pos_y - tile_y) * m_map->tile_width;
    y = m_map->ctr_y - dist_pl_tile_pix.y;
    while (y < m_map->ctr_y - dist_pl_tile_pix.y + m_map->tile_width)
    {
        x = m_map->ctr_x - dist_pl_tile_pix.x;
        while (x < m_map->ctr_x - dist_pl_tile_pix.x + m_map->tile_width)
        {
            if (is_pix_in_minimap(game, x, y) == TRUE)
                my_mlx_pixel_put(&screen->shown_img, x, y, MAP_WALL_COL); 
            x++;
        }
        y++;
    }
}

/* draw the player in the minimap as a circle*/
void    draw_player(t_game *game)
{
    t_screen    *screen;
    t_minimap   *m_map;
    int         x;
    int         y;

    screen = &game->screen;
    m_map = &game->m_map;
    y = m_map->ctr_y - (m_map->pl_width / 2);
    while (y < m_map->ctr_y + (m_map->pl_width / 2))
    {
        x = m_map->ctr_x - (m_map->pl_width / 2);
        while (x < m_map->ctr_x + (m_map->pl_width / 2))
        {
            if (is_inside_circle(game, x, y) == TRUE)
                my_mlx_pixel_put(&screen->shown_img, x, y, MAP_PLAYER_COL);
            x++;
        }
        y++;
    }
}

/* draw the minimap in a square in the down right-hand side of the window */
void    draw_minimap(t_game *game)
{
    int     x;
    int     y;

    init_minimap(game);
    draw_border(game);
    draw_background(game);
    y = 0;
    while (y < game->map_y)
    {
        x = 0;
        while (x < game->map_x)
        {
            if (is_tile_in_minimap(game, x, y) == TRUE)
            {
                if (game->map[y][x] == '1')
                    draw_wall(game, x, y);
            }
            x++;
        }
        y++;
    }
    draw_player(game);
}