#include "../inc/cub3d.h"

#define H 1080/2
#define W 1920/2

int flag = 0;

float to_degrees(float rad)
{
    return (rad * 57.2597);
}

/*
* funzione che inizializza la mappa, la posizione del giocatore e altre costanti del gioco;
*/
void    ft_init1(t_game *game)
{
    //int i = 0;
    //game->pl.pos_x = 5;
    //game->pl.pos_y = 5;     //inizialmente il giocatore è in un punto deciso da me
    //game->pl.view = 3.14159 / 4.0;
    //game->pl.pov = 0;
    game->n_rays = W;
    game->delta_view = game->pl.view/game->n_rays;
    game->game_ended = 0;
    flag = 0;
    printf("pov = %f",to_degrees(game->pl.view));
}

void    ft_init_tex(t_game *game)
{
    
    game->no_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr, 
                            game->no_tex.path, &game->no_tex.width, &game->no_tex.height);
    game->no_tex.tex_addr = mlx_get_data_addr(game->no_tex.tex_img, &game->no_tex.bpp,
                                &game->no_tex.size_line, &game->no_tex.endian);
    game->so_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr, 
                            game->so_tex.path, &game->so_tex.width, &game->so_tex.height);
    game->so_tex.tex_addr = mlx_get_data_addr(game->so_tex.tex_img, &game->so_tex.bpp,
                                &game->so_tex.size_line, &game->so_tex.endian);
    game->ea_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr, 
                            game->ea_tex.path, &game->ea_tex.width, &game->ea_tex.height);
    game->ea_tex.tex_addr = mlx_get_data_addr(game->ea_tex.tex_img, &game->ea_tex.bpp,
                                &game->ea_tex.size_line, &game->ea_tex.endian);
    game->we_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr, 
                            game->we_tex.path, &game->we_tex.width, &game->we_tex.height);
    game->we_tex.tex_addr = mlx_get_data_addr(game->we_tex.tex_img, &game->we_tex.bpp,
                                &game->we_tex.size_line, &game->we_tex.endian);
}

void    ft_init2(t_game *game){
    t_screen *screen;
    t_data *img;
    
    screen = &game->screen;
    img = &game->screen.shown_img;
    screen->ptr = mlx_init();
    screen->win = mlx_new_window(screen->ptr, W, H, "prova");
    img->img = mlx_new_image(screen->ptr, W, H);//changed the first arg of mlx_new_image (earlier it was img->img)
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, 
                                    &img->line_length, &img->endian);
    ft_init_tex(game);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

    if (x > 10 && x < (W - 10) && y > 10 && y < (H - 10))// added this line taken from someone else's code cause there was a seg fault
    {
	    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	    *(unsigned int*)dst = color;
    }
}

/*
* funzione che disegna una colonna di pxnum pxl a partire dalla posizione x,y.
*/
void pixel_col_put(t_screen *screen, int x, int y, int color, int pxnum)
{
    //t_data *img;
    int i;
    (void)pxnum;
    i = 0;
    while (i < pxnum)
    {
        my_mlx_pixel_put(&screen->shown_img, x, y, color);
        i++;
        y++;
    }
}

/*
* funzione che calcola la distanza dell' ostacolo dall'osservatore per ogni raggio della visuale
*/
float get_distance(t_game *game, int w)
{
    float d;
    float ray_a;
    float eye_x;
    float eye_y;
    int ntest_x;// = (int)(posX + distance_to_wall * cos(f_ray_angle))
    int ntest_y; // = (int)(posY + distance_to_wall * sen(f_ray_angle)
    
    //per il calcolo del quadrante
    float mid_block_x;
    float mid_block_y;
    float test_point_x;
    float test_point_y;
    float test_angle;

    d = 0;
    //float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)ScreenWidth()) * fFOV;
    ray_a = game->pl.pov - game->pl.view/2 + game->delta_view * w; //ricontrollare questa
    //ray_a = game->pl.pov - game->pl.view/2 + ( (float)w / (float)W * game->pl.view );
    while (1) //alla fine di questo while in d è presente la ditanza dal muro
    {
        d += 0.01;
        eye_x = d * sin(ray_a);
        eye_y = d * cos(ray_a);
        ntest_x = game->pl.pos_x + eye_x;
        ntest_y = game->pl.pos_y + eye_y;
        if (ntest_x >= game->map_x || ntest_y >= game->map_y)
            return -1;
        if (game->map[ntest_y][ntest_x] == '1')
            break;
        

    }
    //calcolo il quadrante:
    mid_block_x = (float) ntest_x + 0.5; 
    mid_block_y = (float) ntest_y + 0.5;
    
    test_point_x = game->pl.pos_x + d * sin(ray_a);
    test_point_y = game->pl.pos_y + d * cos(ray_a);
    if(test_point_x < 0)
         test_point_x = -test_point_x;
    if(test_point_y < 0)
         test_point_y = -test_point_y;
    test_angle = 1000;

    //if ((test_point_x - mid_block_x) != 0)
    test_angle = atan2f((test_point_y - mid_block_y), (test_point_x - mid_block_x));
    if (test_angle >= -3.14159 * 0.25 && test_angle < 3.14159 * 0.25) //bianco
    {   
        game->screen.orient = 1;
         game->f_sample_x = test_point_y - (float)ntest_y;
    }
    if (test_angle >= 3.14159 * 0.25 && test_angle < 3.14159 * 0.75) // rosso
    {   
        game->screen.orient = 2;
        game->f_sample_x = test_point_x - (float)ntest_x;
    }
    if (test_angle < -3.14159 * 0.25f && test_angle >= -3.14159 * 0.75) //giallo
    {   
        game->screen.orient = 3;
        game->f_sample_x = test_point_x - (float)ntest_x;
    }
    if (test_angle >= 3.14159 * 0.75f || test_angle < -3.14159 * 0.75)
    {   
        game->screen.orient = 4;
        game->f_sample_x = test_point_y - (float)ntest_y;
    }
    // if (test_angle == 1000)
    //     game->screen.q = 4;
    return d;
}


/*
* determina il colore del pixel dalla tex.
* il pixel va preso sulla coordinata x salvata in f_sample_x
* la coordinata y si determina in base all'altezza relativa tra y e wall_h
* y rappresenta a che altezza del muro sto disegnando
*/
int     get_color(t_game *game, int y, int wall_h, t_tex tex)
{
    int color;
    int yt;
    int xt;
    int xpx;

    xpx = tex.width;
    yt = (int)((float)y / wall_h * tex.height);
    xt = (int)(game->f_sample_x * tex.width);
    color = (*(int*)(tex.tex_addr + (4 * xpx * yt) + (4 * xt)));
    return (color);
}

/*
* funzione che disegna una linea sullo schermo per ogni ray
*/
void draw_line(t_screen *screen, int line, float celing_h, t_game *game)
{
    float floor_h;
    float wall_h;
    int y;
    int color;

    floor_h = celing_h;
    wall_h = H - celing_h -floor_h;
    y = 0;
    while (y < celing_h)//sono tra y = 0 e celing
    {
        my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.c_col);
        y++;
    } //lascio nero
    while (y < celing_h + wall_h)
    {
        if (screen->orient == 3)
            color = get_color(game, y - celing_h, wall_h, game->no_tex);
        if (screen->orient == 2)
            color = get_color(game, y - celing_h, wall_h, game->so_tex);
        if (screen->orient == 1)
            color = get_color(game, y - celing_h, wall_h, game->ea_tex);
        if (screen->orient == 4)
            color = get_color(game, y - celing_h, wall_h, game->we_tex);
        my_mlx_pixel_put(&screen->shown_img, line, (y), color);
        y++;
    }
    while (y < H)//sono tra y = 0 e celing
    {
        my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.f_col);
        y++;
    } //lascio nero
}

/*
*
void    update_screen(t_game *game)
{
	t_screen	*screen;
    t_data      img;
    float       d;
    int       celing_h;
    int       floor;
	int			i;
	
    img = game->screen.shown_img;
	screen = &game->screen;

    i = 0;
	while (i < W) //while del raycasting
	{
        d = get_distance(game, i);
        celing_h = H/2 - H/d;
        if (celing_h < 0)
            celing_h = 0;
        floor = H - celing_h;
        draw_pixel(screen, i, 100, 0x00FFFF00);
        //printf("ceilinh H = %d", celing_h);
        i++;
        
	}
}
*/

int    update_window(t_game *game)
{
	t_screen	*screen;
    t_data      *img;
	float       d;
    int       celing_h;
    int       floor;
	int			w;
    
	screen = &game->screen;
    img = &game->screen.shown_img;
    w = 0;
    mlx_clear_window(game->screen.ptr, game->screen.win);
    mlx_destroy_image(screen->ptr, screen->shown_img.img);
    img->img = mlx_new_image(game->screen.ptr, W, H);//changed the first arg of mlx_new_image (earlier it was img->img)
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	while (w < W) //while del raycasting
	{
        d = get_distance(game, w);
        if (d == -1)
            w++;
        else
        {
            celing_h = H/2 - H/d;
            floor = H - celing_h;
            draw_line(screen, w, celing_h, game);   
            w++;
        } 
    }
	mlx_put_image_to_window(screen->ptr, screen->win, img->img, 0, 0);
    return (0);
}

/*
* funzione che controlla se si è andati a sbattere su un muro
* nel qual caso disfa il passo appena fatto
*/
int check_pos(t_game *game) //da completare
{
    int x;
    int y;

    x = game->pl.pos_x;
    y = game->pl.pos_y;
    if (game->map[x][y] == '1')
        return (1);
    return (0);
    // {
    //     game->pl.pos_x -= sin(game->pl.pov) * 0.1;
    //     game->pl.pos_y -= cos(game->pl.pov) * 0.1;
    // }
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W || keycode == KEY_FORWARD)
	{
        //if (!check_pos(game))
        //{
            game->pl.pos_x += sin(game->pl.pov) * 0.2;
            game->pl.pos_y += cos(game->pl.pov) * 0.2;
        //}
    }
    if (keycode == KEY_S || keycode == KEY_BACKWARD)
	{
        game->pl.pos_x -= sin(game->pl.pov) * 0.2;
        game->pl.pos_y -= cos(game->pl.pov) * 0.2; 
    }
    if (keycode == KEY_E || keycode == KEY_RIGHT)
        game->pl.pov += 0.1;
    if (keycode == KEY_Q || keycode == KEY_LEFT)
        game->pl.pov -= 0.1;
    if (keycode == KEY_A)
    {
        float teta;

        teta = game->pl.pov + 3.14/2;
        game->pl.pos_x -= sin(teta) * 0.1;
        game->pl.pos_y -= cos(teta) * 0.1;
    }
    if (keycode == KEY_D)
    {
            float teta;

            teta = game->pl.pov + 3.14/2;
            game->pl.pos_x += sin(teta) * 0.1;
            game->pl.pos_y += cos(teta) * 0.1;
    }
    update_window(game); //commented cause I call update_window from mlx_loop_hook
    return (0);
}

// //int main_function(void)
// int main_function(t_game *game)
// {
//     //t_game game;

//     //game.tex.path = "bluestone.xpm";
//     ft_init1(game);
//     ft_init2(game);
//     //update_window(&game);
    
//     mlx_hook(game->screen.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
//     mlx_loop_hook(game->screen.ptr, &update_window, &game);
//     mlx_loop(game->screen.ptr);

//     return (0);
// }