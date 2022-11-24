#include "../inc/cub3d.h"

# define MAP_WALL_COL 0x70202020
# define MAP_BORDER_COL 0x70FFFFFF
# define MAP_EMPTY_COL 0x70FFFFFF
# define MAP_PLAYER_COL 0x000000FF
# define MAP_BORDER_WIDTH 5
# define MAP_TILE_WIDTH 25
# define MAP_PLAYER_WIDTH 15
# define DIST_MAP_WIN 30
# define MAP_START_UP 3 * W / 4
# define MAP_START_LEFT 3 * W / 4

void    draw_horiz_lines(t_game *game, int x, int *y)
{
    int         d_side; //the start of the down side of the rectangle
    t_screen    *screen;
    int         i;
    
    d_side = H - MAP_BORDER_WIDTH - DIST_MAP_WIN; 
    screen = &game->screen;
    while (x < W - DIST_MAP_WIN)
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

void    draw_vert_lines(t_game *game, int x, int y)
{
    int         r_side; //the start of the right side of the rectangle
    t_screen    *screen;
    int         i;

    r_side = W - MAP_BORDER_WIDTH - DIST_MAP_WIN; 
    screen = &game->screen;
    while (y < H - MAP_BORDER_WIDTH - DIST_MAP_WIN)
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

void    draw_border(t_game *game)
{
    int         x;
    int         y;
    
    y = MAP_START_UP;
    x = MAP_START_LEFT;
    draw_horiz_lines(game, x, &y);
    draw_vert_lines(game, x, y);
}

void    put_wall(t_game *game, int x, int y)
{

}

t_coord    put_player(t_game *game)
{
    t_screen    *screen;
    t_coord     centre;
    int         x;
    int         y;

    screen = &game->screen;
    centre.x = (MAP_START_LEFT + (W - DIST_MAP_WIN)) / 2;
    centre.y = (MAP_START_UP + (H - DIST_MAP_WIN)) / 2;
    y = centre.y - (MAP_PLAYER_WIDTH / 2);
    while (y < centre.y + (MAP_PLAYER_WIDTH / 2))
    {
        x = centre.x - (MAP_PLAYER_WIDTH / 2);
        while (x < centre.x + (MAP_PLAYER_WIDTH / 2))
        {
            my_mlx_pixel_put(&screen->shown_img, x, y, MAP_PLAYER_COL);
            x++;
        }
        y++;
    }
    return (centre);
}

void    put_empty(t_game *game, int x, int y)
{

}

void    put_minimap(t_game *game)
{
    int     x;
    int     y;
    t_coord centre;

    draw_border(game);// non necessario
    centre = put_player(game);
    y = centre.x;
    while (y < game->map_y)
    {
        x = 0;
        while (x < game->map_x)
        {
            if (game->map[y][x] == '1')
                put_wall(game, x, y);
            //else if (x == (int)game->pl.pos_x && y == (int)game->pl.pos_y)
                //put_player(game, x, y);
            else
                put_empty(game, x, y);
            x++;
        }
        y++;
    }
}