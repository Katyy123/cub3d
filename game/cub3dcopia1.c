

#include "../inc/cub3d.h"

#define H 1080
#define W 1920
#define X 0
#define Y 1




//per poter usare algorimo dda ho divuto cambiare un po' di cose, 
// se usi questo file qui nella tua repository al posto di cube3d.c (modificare makefile)
// dovresti poter cambiare solo la funzione increment_d. 


double to_degrees(double rad)
{
    return (rad * 57.2597);
}

/*
* funzione che inizializza a zero i valori della struttura rc
*/
void    ft_init_rc(t_rc *rc)
{
    rc->ntest_x = 0;
    rc->ntest_y = 0;
    rc->mid_block_x = 0;
    rc->mid_block_y = 0;
    rc->test_point_x = 0;
    rc->test_point_y = 0;
    rc->test_angle = 0;
}

/*
* funzione che inizializza la mappa, la posizione del giocatore e altre costanti del gioco;
*/
void    ft_init1(t_game *game)
{
    game->pl.pos_x += 0.5;
    game->pl.pos_y += 0.5;
    game->n_rays = W;
    game->delta_view = game->pl.view/game->n_rays;
    game->game_ended = 0;
    game->mov.m_fwrd = 0;
    game->mov.m_bwrd = 0;
    game->mov.m_lft = 0;
    game->mov.m_rght = 0;
    game->mov.r_l = 0;
    game->mov.r_r = 0;
    game->nsoe = 0;
    game->ray.cos_a = 0.0;
    game->ray.sin_a = 0.0;
    game->ray.m = 0.0;
    game->ray.sx = 0.0;
    game->ray.sy = 0.0;
    ft_init_rc(&game->r);
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

    if (x > 10 && x < (W - 10) && y > 10 && y < (H - 10))
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
* funzione che determina l'orientamento della parte incontrata e setta il valore di 
* f_sample_X che serve a capire la coordinata x per il sampling della texture
*/
void get_orient(t_game *game)
{
    double   test_angle;

    test_angle = game->r.test_angle;
    if (test_angle >= -M_PI * 0.25 && test_angle < M_PI * 0.25)
    {   
        game->screen.orient = 1;
    }
    if (test_angle >= M_PI * 0.25 && test_angle < M_PI * 0.75)
    {   
        game->screen.orient = 2;
    }
    if (test_angle < -M_PI * 0.25f && test_angle >= -M_PI * 0.75)
    {   
        game->screen.orient = 3;
    }
    if (test_angle >= M_PI * 0.75f || test_angle < -M_PI * 0.75)
    {   
        game->screen.orient = 4;
    }
}

double my_abs(double a)
{
    if (a < 0)
        return (-a);
    return (a);
}

void    set_orient(t_game *game, double cos_a, double sin_a, char xy)
{
    if (cos_a > 0 && sin_a > 0)
    {
        if (xy == 'x')
            game->nsoe = 'N';
        else
            game->nsoe = 'O';
    }
    else if (cos_a > 0 && sin_a < 0)
    {
        if (xy == 'x')
            game->nsoe = 'S';
        else
            game->nsoe = 'O';
    }
    else if (cos_a < 0 && sin_a > 0)
    {
        if (xy == 'x')
            game->nsoe = 'N';
        else
            game->nsoe = 'E';
    }
    else// (cos_a < 0 && sin_a < 0)
    {
        if (xy == 'x')
            game->nsoe = 'S';
        else
            game->nsoe = 'E';
    }
}   

void    first_step(t_game *game, int *eye, int *step, double *ip)
{
    eye[X] = game->pl.pos_x;
    eye[Y] = game->pl.pos_y;
    if (game->ray.cos_a < 0)
    {
        step[X] = -1;
        ip[X] = (game->pl.pos_x - (double)eye[X]) * game->ray.sx;
    }
    else
    {
        step[X] = 1;
        ip[X] = (((double)eye[X] + 1) - game->pl.pos_x) * game->ray.sx;
    }
    if (game->ray.sin_a < 0)
    {
        step[Y] = -1;
        ip[Y] = (game->pl.pos_y - (double)eye[Y]) * game->ray.sy;
    }
    else
    {
        step[Y] = 1;
        ip[Y] = (((double)eye[Y] + 1) - game->pl.pos_y) * game->ray.sy;
    }
}

/*
* incrementa di una tile lungo x, aggiorna la distanza e controlla se cé il muro
*/
t_bool    increment_x(t_game *game, int *step, int *eye, double *ip, double *d)
{
    t_bool wall;

    wall = FALSE;
    eye[X] += step[X]; //devo controllare il muro subito dopo questo!! (forse) ...
    if (!(game->map[eye[Y]][eye[X]] == '1')) // se non cè un muro aumento ancora l'ipotenusa
    {
        ip[X] += game->ray.sx;
        *d = ip[X];
        game->f_sample_x =(game->pl.pos_y + *d * game->ray.sin_a) - (int)(game->pl.pos_y + *d * game->ray.sin_a); 
    }
    else
    {
        wall = TRUE;
        *d = ip[X];
        game->f_sample_x =(game->pl.pos_y + *d * game->ray.sin_a) - (int)(game->pl.pos_y + *d * game->ray.sin_a);
        set_orient(game, game->ray.cos_a, game->ray.sin_a, 'y');
    }
    
    return (wall);
}


/*
* incrementa di una tile lungo y, aggiorna la distanza e controlla se cé il muro
*/
t_bool    increment_y(t_game *game, int *step, int *eye, double *ip, double *d)
{
    t_bool wall;

    wall = FALSE;
    eye[Y] += step[Y]; //devo controllare il muro subito dopo questo!! (forse) ...
    if (!(game->map[eye[Y]][eye[X]] == '1')) // se non cè un muro aumento ancora l'ipotenusa
    {
        ip[Y] += game->ray.sy;
        *d = ip[Y];
        game->f_sample_x =(game->pl.pos_x + *d * game->ray.cos_a) - (int)(game->pl.pos_x + *d * game->ray.cos_a);
    }
    else
    {
        wall = TRUE;
        *d = ip[Y];
        game->f_sample_x =(game->pl.pos_x + *d * game->ray.cos_a) - (int)(game->pl.pos_x + *d * game->ray.cos_a);
        set_orient(game, game->ray.cos_a, game->ray.sin_a, 'x');
    }
    return (wall);
}

/*
* funzione che scrive in d la distanza dal muro con dda
*/
void    increment_d(double *d, t_game *game, int *step, int *eye, double *ip)
{
    t_bool wall;

    wall = FALSE;
    first_step(game, eye, step, ip);
    while (!wall)
    {
        if (ip[X] >= ip[Y])
            wall = increment_y(game, step, eye, ip, d);
        else
            wall = increment_x(game, step, eye, ip, d);
    } 
}

/*
* funzione che calcola la distanza dell' ostacolo dall'osservatore per ogni raggio della visuale
*/
double get_distance(t_game *game, int w)
{
    double   d;
    double   ray_a;
    int      step[2];
    int      eye[2];
    double   ip[2];

    d = 0;
    ray_a =  game->pl.pov - game->pl.view/2 + game->delta_view * w; //ricontrollare questa
    game->ray.m = tan(ray_a);  //tangente o coefficente angolare
    game->ray.sx = sqrt(1 + game->ray.m*game->ray.m); //passo sulla x che corrisponde al passo di una casella sulla y
    game->ray.sy = sqrt(1 + (1/game->ray.m)*(1/game->ray.m)); //passo sulla y che corrisponde al passo di una casella sulla x
    game->ray.cos_a = cos(ray_a);
    game->ray.sin_a = sin(ray_a);
    increment_d(&d, game, step, eye, ip);
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
    yt = (int)((double)y / wall_h * tex.height);
    xt = (int)(game->f_sample_x * tex.width);
    color = (*(int*)(tex.tex_addr + (4 * xpx * yt) + (4 * xt)));
    return (color);
}

int draw_ceiling(t_game *game, double celing_h, int line)
{
    t_screen    *screen;
    int         y;

    y = 0;
    screen = &game->screen;
    while (y < celing_h)
    {
        my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.c_col);
        y++;
    }
    return (y);
}

t_tex ret_right_tex(t_game *game)
{
    char orient;

    orient = game->nsoe;
    if (orient == 'N')
        return (game->no_tex);
    if (orient == 'S')
        return (game->so_tex);
    if (orient == 'E')
        return (game->ea_tex);
    if (orient == 'W')
        return (game->we_tex);
    else
        return (game->we_tex);
}

/*
* funzione che disegna una linea sullo schermo per ogni ray
*/
void draw_line(t_screen *screen, int line, double celing_h, t_game *game)
{
    double floor_h;
    double wall_h;
    int y;

    floor_h = celing_h;
    wall_h = H - celing_h -floor_h;
    y = draw_ceiling(game, celing_h, line);
    while (y < celing_h + wall_h)
    {
        my_mlx_pixel_put(&screen->shown_img, line, (y), 
                        get_color(game, y - celing_h, wall_h,
                        ret_right_tex(game)));
        y++;
    }
    while (y < H)
    {
        my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.f_col);
        y++;
    }
}

void    update_pos(t_game *game)
{
    double teta;
    
    if (game->mov.m_fwrd == 1 && !wall_f1(game) && !wall_f2(game))
    {
        game->pl.pos_x += cos(game->pl.pov) * 0.2;
        game->pl.pos_y += sin(game->pl.pov) * 0.2;
    }
    else if (game->mov.m_bwrd == 1 && !wall_b1(game) && !wall_b2(game))
    {
        game->pl.pos_x -= cos(game->pl.pov) * 0.2;
        game->pl.pos_y -= sin(game->pl.pov) * 0.2;
    }
    else if  (game->mov.m_rght == 1 && !wall_dx(game))
    {
        teta = game->pl.pov + M_PI/2;
        game->pl.pos_x += cos(teta) * 0.1;
        game->pl.pos_y += sin(teta) * 0.1;
    }
    else if  (game->mov.m_lft == 1 && !wall_sx(game))
    {
        teta = game->pl.pov + M_PI/2;
        game->pl.pos_x -= cos(teta) * 0.1;
        game->pl.pos_y -= sin(teta) * 0.1;
    }
    else if (game->mov.r_r == 1)
        game->pl.pov += 0.05;
    else if (game->mov.r_l == 1)
        game->pl.pov -= 0.05;
}

int    update_window(t_game *game)
{
	t_screen	*screen;
    t_data      *img;
	double       d;
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
    update_pos(game);
    while (w < W) //while del raycasting
	{
        d = get_distance(game, w);
        celing_h = H/2 - H/d;
        floor = H - celing_h;
        draw_line(screen, w, celing_h, game);   
        w++;
    }
	mlx_put_image_to_window(screen->ptr, screen->win, img->img, 0, 0);
    return (0);
}

int key_rlease(int keycode, t_game *game)
{
    if (keycode == KEY_W || keycode == KEY_FORWARD)
        game->mov.m_fwrd = 0;
    if (keycode == KEY_S || keycode == KEY_BACKWARD)// modified from "if" to "else if" (check if it is ok)
        game->mov.m_bwrd = 0;
    if (keycode == KEY_E || keycode == KEY_RIGHT)// modified from "if" to "else if" (check if it is ok)
        game->mov.r_r = 0;
    if (keycode == KEY_Q || keycode == KEY_LEFT)// modified from "if" to "else if" (check if it is ok)
        game->mov.r_l = 0;
    if (keycode == KEY_A)// modified from "if" to "else if" (check if it is ok)
        game->mov.m_lft = 0;
    if (keycode == KEY_D)// modified from "if" to "else if" (check if it is ok)
        game->mov.m_rght = 0;
    return (0);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W || keycode == KEY_FORWARD)
        game->mov.m_fwrd = 1;
    if (keycode == KEY_S || keycode == KEY_BACKWARD)// modified from "if" to "else if" (check if it is ok)
        game->mov.m_bwrd = 1;
    if (keycode == KEY_E || keycode == KEY_RIGHT)// modified from "if" to "else if" (check if it is ok)
        game->mov.r_r = 1;
    if (keycode == KEY_Q || keycode == KEY_LEFT)// modified from "if" to "else if" (check if it is ok)
        game->mov.r_l = 1;
    if (keycode == KEY_A)// modified from "if" to "else if" (check if it is ok)
        game->mov.m_lft = 1;
    if (keycode == KEY_D)// modified from "if" to "else if" (check if it is ok)
        game->mov.m_rght = 1;
    if (keycode == KEY_ESC)
        end_program(game);
    update_window(game); //commented cause I call update_window from mlx_loop_hook
    return (0);
}