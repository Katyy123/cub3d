#include "../inc/cub3d.h"

/* draw the border of the minimap */
void    draw_border(t_game *game)
{
    int         x;
    int         y;
    t_minimap   *m_map;
    t_screen    *screen;

    m_map = &game->m_map;
    screen = &game->screen;
    y = m_map->bd_start_up;
    while (y <= m_map->bd_end_d)
    {
        x = m_map->bd_start_l;
        while(x <= m_map->bd_end_r)
        {
            my_mlx_pixel_put(&screen->shown_img, x, y, MAP_BORDER_COL);
            x++;
        }
        y++;
    }
}

/* draw the background of the minimap (it is inside the border) */
void    draw_background(t_game *game)
{
    int x;
    int y;
    t_screen    *screen;
    t_minimap   *m_map;

    screen = &game->screen;
    m_map = &game->m_map;
    y = m_map->start_up;
    while (y < m_map->end_d)
    {
        x = m_map->start_l;
        while (x < m_map->end_r)
        {
            my_mlx_pixel_put(&screen->shown_img, x, y, MAP_BACK_COL);
            x++;
        }
        y++;
    }
}