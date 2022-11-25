#include "../inc/cub3d.h"

/* draw the horizontal lines of the minimap border */
void    draw_horiz_lines(t_game *game, int x, int *y)
{
    int         d_side; //the start of the down side of the square
    t_screen    *screen;
    int         i;
    t_minimap   *m_map;
    
    m_map = &game->m_map;
    d_side = m_map->end_d; 
    screen = &game->screen;
    while (x < m_map->bd_end_r)
    {
        i = 0;
        while (i++ < MAP_BORDER_WIDTH)
        {
            my_mlx_pixel_put(&screen->shown_img, x, *y, MAP_BORDER_COL);
            my_mlx_pixel_put(&screen->shown_img, x, d_side, MAP_BORDER_COL);
            (*y)++;
            d_side++;
        }
        x++;
    }
}

/* draw the vertical lines of the minimap border */
void    draw_vert_lines(t_game *game, int x, int y)
{
    int         r_side; //the start of the right side of the square
    t_screen    *screen;
    int         i;
    t_minimap   *m_map;

    m_map = &game->m_map;
    r_side = m_map->end_r; 
    screen = &game->screen;
    while (y < m_map->end_d)
    {
        i = 0;
        while (i++ < MAP_BORDER_WIDTH)
        {
            my_mlx_pixel_put(&screen->shown_img, x, y, MAP_BORDER_COL);
            my_mlx_pixel_put(&screen->shown_img, r_side, y, MAP_BORDER_COL);
            x++;
            r_side++;
        }
        y++;
    }
}

/* draw the border of the minimap */
void    draw_border(t_game *game)
{
    int         x;
    int         y;
    t_minimap   *m_map;
    
    m_map = &game->m_map;
    y = m_map->bd_start_up;
    x = m_map->bd_start_l;
    draw_horiz_lines(game, x, &y);
    draw_vert_lines(game, x, y);
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