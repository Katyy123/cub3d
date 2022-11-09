#include "../inc/cub3d.h"

#define H 1080/2
#define W 1920/2

int flag = 0;

float to_degrees(float rad)
{
    return (rad * 57.2597);
}

// char map_init[20][11]=  {
//                         {'1','1','1','1','1','1','1','1','1','1','\0'},
//                         {'1','1','0','0','1','1','0','0','1','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','1','0','0','0','0','1','0','0','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','0','0','0','0','p','0','0','0','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','0','0','0','0','0','0','1','0','1','\0'},
//                         {'1','1','0','0','0','0','0','0','1','1','\0'},
//                         {'1','1','1','1','1','1','1','1','1','1','\0'},
//                         {'1','1','1','1','1','1','1','1','1','1','\0'},
//                         {'1','1','0','0','1','0','0','0','1','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','0','0','1','0','0','0','0','0','1','\0'},
//                         {'1','0','0','0','0','p','1','0','0','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','0','0','0','0','0','0','0','0','1','\0'},
//                         {'1','1','0','0','0','1','0','0','1','1','\0'},
//                         {'1','1','1','1','1','1','1','1','1','1','\0'},
//                         };

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*source;
	unsigned char	*dest;

	if (!dst && !src)
		return (NULL);
	i = 0;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}

int     ft_strlen(const char *str)
{
	int	len;

	if(!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*out;

	len = ft_strlen((char *)str) + 1;
	out = malloc(len * sizeof(char));
	if (!out)
		return (NULL);
	ft_memcpy(out, str, len);
	return (out);
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
    // i = 0;
    // while (i < 10)
    // {
    //     printf("map[%d] = %s", i, map_init[i]);
    //     printf("\n");
    //     i++;
    // }


}

/*
* funzione che inizializza le texture. per ora gestisce un unica text.
*/
void    ft_init_tex(t_tex *t, void *mlx)// a partire dalla text creo una vera e propria immagine
{
    t->tex_img = mlx_xpm_file_to_image(mlx, t->path, &t->width, &t->height);
    t->tex_addr = mlx_get_data_addr(t->tex_img, &t->bpp, &t->size_line, &t->endian);
}

void    ft_init2(t_game *game){
    t_screen *screen;
    t_data *img;
    
    screen = &game->screen;
    img = &game->screen.shown_img;
    screen->ptr = mlx_init();
    screen->win = mlx_new_window(screen->ptr, W, H, "prova");
    img->img = mlx_new_image(screen->ptr, W, H);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
    ft_init_tex(&game->no_tex, screen->ptr);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

    if (x > 10 && x < (W - 10) && y > 10 && y < (H - 10))// to check
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
        if (game->map[ntest_y][ntest_x] == '1')
            break;
         if (ntest_x >= 10 || ntest_y >= 10)
            return -1;

    }
    //calcolo il quadrante:
    mid_block_x = (float) ntest_x + 0.5; 
    mid_block_y = (float) ntest_y + 0.5;
    
    test_point_x = game->pl.pos_x + d * sin(ray_a);
    test_point_y = game->pl.pos_y + d * cos(ray_a);
    test_angle = 1000;

    //if ((test_point_x - mid_block_x) != 0)
    test_angle = atan2f((test_point_y - mid_block_y), (test_point_x - mid_block_x));
    if (test_angle >= -3.14159 * 0.25 && test_angle < 3.14159 * 0.25) //bianco
    {   game->screen.q = 1;
         game->f_sample_x = test_point_y - (float)ntest_y;
    }
    if (test_angle >= 3.14159 * 0.25 && test_angle < 3.14159 * 0.75) // rosso
    {   game->screen.q = 2;
        game->f_sample_x = test_point_x - (float)ntest_x;
    }
    if (test_angle < -3.14159 * 0.25f && test_angle >= -3.14159 * 0.75) //giallo
    {   game->screen.q = 3;
        game->f_sample_x = test_point_x - (float)ntest_x;
    }
    if (test_angle >= 3.14159 * 0.75f || test_angle < -3.14159 * 0.75)
    {   game->screen.q = 4;
        game->f_sample_x = test_point_y - (float)ntest_y;
    }
    // if (test_angle == 1000)
    //     game->screen.q = 4;
    return d;
}

t_tex *select_text(t_game *game){

    return (&game->no_tex);
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

    if (screen->q == 1)
        color = 0x00FFFFFF;
    if (screen->q == 2)
        color = 0x00FF0000;
    if (screen->q == 3)
        color = 0x00BBBBBB;
    if (screen->q == 4)
        color = 0x00FFFF00;

    floor_h = celing_h;
    wall_h = H - celing_h -floor_h;
    y = 0;
    while (y < celing_h)//sono tra y = 0 e celing
        y++; //lascio nero
    while (y < celing_h + wall_h)
    {
        //if (screen->q == 1)
        color = get_color(game, y - celing_h, wall_h, game->no_tex);
        my_mlx_pixel_put(&screen->shown_img, line, (y), color);
        y++;
    }

    //sono tra celing e 
    // floor_h = celing_h;
    // wall_h = H - celing_h - floor_h;
    // y = 0;
    // if (flag == 1)
    // {
    //     pixel_col_put(screen, line, y, 0x00FF0000, H);
    //     return ;
    // }
    // pixel_col_put(screen, line, y, 0x00FF0000, celing_h);
    // y = H - floor_h;
    // pixel_col_put(screen, line, y, 0x00FF0000, floor_h);

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
    img->img = mlx_new_image(img->img, W, H);
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

// int loop(t_game *game){
//     //update_screen(game);
    
// 	update_window(game);
//    return (0);
// }

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
        if (!check_pos(game))
        {
            game->pl.pos_x += sin(game->pl.pov) * 0.1;
            game->pl.pos_y += cos(game->pl.pov) * 0.1;
        }
    }
    if (keycode == KEY_S || keycode == KEY_BACKWARD)
	{
        game->pl.pos_x -= sin(game->pl.pov) * 0.1;
        game->pl.pos_y -= cos(game->pl.pov) * 0.1; 
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
    //update_window(game);
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