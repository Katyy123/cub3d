
#include "inc/cub3d.h"

#define H 1080/2
#define W 1920/2

int color;

char map_init[10][11]=  {
                        {'1','1','1','1','1','1','1','1','1','1','\0'},
                        {'1','0','0','0','0','0','0','0','0','1','\0'},
                        {'1','1','0','0','1','0','0','0','0','1','\0'},
                        {'1','0','0','0','1','1','0','1','0','1','\0'},
                        {'1','0','0','0','0','0','0','0','0','1','\0'},
                        {'1','0','1','0','0','p','0','0','0','1','\0'},
                        {'1','0','1','0','0','0','0','0','0','1','\0'},
                        {'1','0','1','1','0','0','0','0','0','1','\0'},
                        {'1','0','0','0','0','0','0','0','0','1','\0'},
                        {'1','1','1','1','1','1','1','1','1','1','\0'},
                        };

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
    int i = 0;
    game->pl.pos_x = 5;
    game->pl.pos_y = 5;     //inizialmente il giocatore è in un punto deciso da me
    game->pl.view = 3.14/2.5;
    game->pl.pov = 0;
    game->delta_view = game->pl.view/W;
    game->n_rays = W;
    game->game_ended = 0;
    
    i = 0;
    while (i < 10)
    {
        printf("map[%d] = %s", i, map_init[i]);
        printf("\n");
        i++;
    }


}

void    ft_init2(t_game *game){
    t_screen *screen;
    t_data *img;
    
    screen = &game->screen;
    img = &game->screen.shown_img;
    screen->ptr = mlx_init();
    screen->win = mlx_new_window(screen->ptr,W, H, "prova");
    img->img = mlx_new_image(img->img, W, H);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
* funzione che conrolla se il punto di muro incontrato è il bordo del muro
*/
// int check_border(t_game *game, int x, int y)
// {

// }

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
    d = 0;
    ray_a = game->pl.pov - game->pl.view/2 + game->delta_view * w;
    // printf("X = %f, Y = %f, POV = %f\n", game->pl.pos_x, game->pl.pos_y, game->pl.pov);
    while (1)
    {
        d += 0.01;
        eye_x = d * sin(ray_a);
        eye_y = d * cos(ray_a);
        ntest_x = game->pl.pos_x + eye_x;
        ntest_y = game->pl.pos_y + eye_y;
        if (map_init[ntest_y][ntest_x] == '1')
            break;
        // if (ntest_x >= 10 || ntest_y >= 10)
        //     return 100;
    }
    //check_border(game, ntest_x, ntest_y);
    return d;
}

/*
* funzione che disegna una linea sullo schermo per ogni ray
*/
void draw_line(t_screen *screen, int line, float celing_h)
{
    float floor_h;
    float wall_h;
    int y;

    floor_h = celing_h;
    wall_h = H - celing_h - floor_h;
    y = 0;
    pixel_col_put(screen, line, y, 0x00FF0000, celing_h);
    y = H - floor_h;
    pixel_col_put(screen, line, y, 0x00FF0000, floor_h);
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
	int			i;
    
	screen = &game->screen;
    img = &game->screen.shown_img;
    i = 0;
    mlx_clear_window(game->screen.ptr, game->screen.win);
    mlx_destroy_image(screen->ptr, screen->shown_img.img);
    img->img = mlx_new_image(img->img, W, H);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	while (i < W) //while del raycasting
	{
        d = get_distance(game, i);
        if (i == W/2){
            printf("distance = %f\n", d);
        }
        celing_h = H/2 - H/d;
        floor = H - celing_h;
        draw_line(screen, i, celing_h);   
        i++;
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
void check_pos(t_game *game) //da completare
{
    int x;
    int y;

    x = game->pl.pos_x;
    y = game->pl.pos_y;
    if (map_init[x][y] == '1')
    {
        game->pl.pos_x -= sin(game->pl.pov) * 0.1;
        game->pl.pos_y -= cos(game->pl.pov) * 0.1;
    }
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W || keycode == KEY_FORWARD)
	{
        game->pl.pos_x += sin(game->pl.pov) * 0.1;
        game->pl.pos_y += cos(game->pl.pov) * 0.1;
        update_window(game);
        check_pos(game);
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
    printf("\t\t\tx = %f, y = %f, pov = %f\n", game->pl.pos_x, game->pl.pos_y, game->pl.pov);
    update_window(game);
    return (0);
}

int main(void)
{
    t_game game;

    ft_init1(&game);
    ft_init2(&game);
    update_window(&game);
    mlx_hook(game.screen.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
    //mlx_loop_hook(game.screen.ptr, &update_window, &game);
    mlx_loop(game.screen.ptr);

    return (0);
}