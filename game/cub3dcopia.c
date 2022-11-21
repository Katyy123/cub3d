


#include "../inc/cub3d.h"

#define H 1080 / 2
#define W 1920 / 2

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


double dda_incr(double d, t_game *game, double m, double sx, double sy, double ray_a)
{
    //Dx = m*sx Dy = m*sy
    (void)m;
    double n_x = 0.0;// new pos x
    double n_y = 0.0;// new pos y
    double ipotenusa_y = 0;
    double ipotenusa_x = 0;
    double cos_a = cos(ray_a);
    double sin_a = sin(ray_a);

    double incr_x= 0.0;
    double incr_y= 0.0;

    n_x = game->pl.pos_x + (d * cos_a);
    n_y = game->pl.pos_y + (d * sin_a);

    if (sin_a == 0 && cos_a < 0)
        return(n_x - (int)n_x);
    else if (sin_a == 0 && cos_a > 0)
        return(1 - n_x - (int)n_x);
    else if (sin_a < 0 && cos_a == 0)
        return(n_y - (int)n_y);
    else if (sin_a > 0 && cos_a == 0)
        return(1 - n_y - (int)n_y);
    if (sin_a > 0 && cos_a > 0) //I
    {
        incr_x = 1 - n_x - (int)n_x;
        incr_y = 1 - n_y - (int)n_y;
        if (incr_x == 0)
            incr_x = 1;
        if (incr_y == 0)
            incr_y = 1;
        
    }
    else if (sin_a > 0 && cos_a < 0)//II 
    {
        incr_x = n_x - (int)n_x;
        incr_y = 1 - n_y - (int)n_y;
        if (incr_x == 0)
            incr_x = 1;
        if (incr_y == 0)
            incr_y = 1;
    }
    else if (sin_a < 0 && cos_a < 0)//III ok
    {
        incr_x = n_x - (int)n_x;
        incr_y = n_y - (int)n_y;
        if (incr_x == 0)
            incr_x = 1;
        if (incr_y == 0)
            incr_y = 1;
    }
    else if (sin_a < 0 && cos_a > 0)//IIII ok 
    {
        incr_x = 1 - n_x - (int)n_x;
        incr_y = n_y - (int)n_y;
        if (incr_x == 0)
            incr_x = 1;
        if (incr_y == 0)
            incr_y = 1;
    } 
    ipotenusa_y = incr_y * sy;
    ipotenusa_x = incr_x * sx;
    if (ipotenusa_x <= ipotenusa_y)
        return (ipotenusa_x);
    return (ipotenusa_y);

}


/*
* funzione che ritorna 1 quando è stata incontrata una parete, o quando
* sono uscito dalla mappa, nel frattempo aggiorna il valore della distanza dall
* osservatore (d) che è passata per indirizzo.
*/
t_bool increment_d(double *d, t_game *game, double ray_a)
{
    int     stepx; // passo sulla x per andare all'intersezione successiva
    int     stepy; // passo sulla y per andare all'intersezione successiva
    int   eye_x; //indice x della casella da controllare nella mappa
    int   eye_y; //indice y della casella da controllare nella mappa
    double   ipx; //distanza lungo x dalla casella che sto controllando
    double   ipy; //distanza lungo y dalla casella che sto controllando

    double m = tan(ray_a); //tangente o coefficente angolare
    double sx = sqrt(1 + m*m); //passo sulla x che corrisponde al passo di una casella sulla y
    double sy = sqrt(1 + (1/m)*(1/m)); //passo sulla y che corrisponde al passo di una casella sulla x
    double cos_a = cos(ray_a);
    double sin_a = sin(ray_a);

    eye_x = game->pl.pos_x; //all'inizio la posizione da controllare parte dal giocatore
    eye_y = game->pl.pos_y;

    t_bool wall;

    wall = FALSE;
   
// con questi if else calcolo se lungo x e lungo y devo aumentare o diminuire di uno per andare nella 
// prox. casella
    if (cos_a < 0)
    {
        stepx = -1;
        ipx = (game->pl.pos_x - (double)eye_x) * sx;
    }
    else
    {
        stepx = 1;
        ipx = (((double)eye_x + 1) - game->pl.pos_x) * sx;
    }

    while (!wall)
    {
        if (game->map[eye_y][eye_x] == '1')
            wall = TRUE;
        eye_x += stepx;
        ipx += sx;
        
    }


    eye_x = game->pl.pos_x;
    eye_y = game->pl.pos_y;

// con questi if else calcolo se lungo x e lungo y devo aumentare o diminuire di uno per andare nella 
// prox. casella
    if (sin_a < 0)
    {
        stepy = -1;
        ipy = (game->pl.pos_y - (double)eye_y) * sy;
    }
    else
    {
        stepy = 1;
        ipy = (((double)eye_y + 1) - game->pl.pos_y) * sy;
    }

    
    wall = FALSE;
    while (!wall)
    {
        if (game->map[eye_y][eye_x] == '1')
            wall = TRUE;
        eye_y += stepy;
        ipy += sy;
        
    }
    
    // se la ditanza dall'intersezione sulla x è maggiore di quella sulla y prende in considerazione quella 
    // sulla y
    if (ipx > ipy)
    {
        *d = ipy;
        game->f_sample_x =(game->pl.pos_x + *d * cos_a) - (int)(game->pl.pos_x + *d * cos_a); //mi serve per calcolare in che punto della texture andare a prendere i colori!       
    }
    else
    {
        *d = ipx;
        game->f_sample_x =(game->pl.pos_y + *d * sin_a) - (int)(game->pl.pos_y + *d * sin_a);            
    }

    //mi servono per mettere bene le texture
    game->r.ntest_x = eye_x;
    game->r.ntest_y = eye_y;
    game->r.test_point_x = game->pl.pos_x + *d * cos_a;
    game->r.test_point_y = game->pl.pos_y + *d * sin_a;
    
    return (TRUE);

    
    
}

/*
* funzione che calcola la distanza dell' ostacolo dall'osservatore per ogni raggio della visuale
*/
// double get_distance(t_game *game, int w)
// {
//     double   d;
//     double   ray_a;
//     t_bool  wall;
    
//     wall = FALSE;
//     d = 0;
//     ray_a =  game->pl.pov - game->pl.view/2 + game->delta_view * w; //ricontrollare questa
//     //while (!wall)
//     wall = increment_d(&d, game, ray_a);
//     if (w > W/2 - 40 && w < W/2 + 40)
//         printf("ray_a = %f => d = %f\t cos_a = %f sin_a = %f\n ", to_degrees(ray_a), d, cos(ray_a), sin(ray_a));
//     //calcolo il quadrante:
//     game->r.mid_block_x = (double) game->r.ntest_x + 0.5; 
//     game->r.mid_block_y = (double) game->r.ntest_y + 0.5;

//     game->r.test_angle = 1000; //why?
//     game->r.test_angle = atan2f((game->r.test_point_y - game->r.mid_block_y),
//                                  (game->r.test_point_x - game->r.mid_block_x));
//     get_orient(game);


//     return d;

// }

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
    int orient;

    orient = game->screen.orient;
    if (orient == 3)
        return (game->no_tex);
    if (orient == 2)
        return (game->so_tex);
    if (orient == 1)
        return (game->ea_tex);
    if (orient == 4)
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
        // my_mlx_pixel_put(&screen->shown_img, line, (y), 
        //                 get_color(game, y - celing_h, wall_h,
        //                 ret_right_tex(game)));
        my_mlx_pixel_put(&screen->shown_img, line, (y), 
                        get_color(game, y - celing_h, wall_h,
                        game->no_tex));
        y++;
    }
    while (y < H)
    {
        my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.f_col);
        y++;
    }

    /*
    double floor_h;
    double wall_h;
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
    */
}

/*
*
void    update_screen(t_game *game)
{
	t_screen	*screen;
    t_data      img;
    double       d;
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

void    update_pos(t_game *game)
{
    double teta;
    
    if (game->mov.m_fwrd == 1 && !wall_f1(game) && !wall_f2(game))
    {
        game->pl.pos_x += cos(game->pl.pov) * 0.2;
        game->pl.pos_y += sin(game->pl.pov) * 0.2;//scambiati sen e cos
    }
    else if (game->mov.m_bwrd == 1 && !wall_b1(game) && !wall_b2(game))
    {
        game->pl.pos_x -= cos(game->pl.pov) * 0.2;
        game->pl.pos_y -= sin(game->pl.pov) * 0.2;//scambiati sen e cos
    }
    else if  (game->mov.m_rght == 1 && !wall_dx(game))
    {
        teta = game->pl.pov + M_PI/2;
        game->pl.pos_x += cos(teta) * 0.1;
        game->pl.pos_y += sin(teta) * 0.1; //scambiati sen e cos
    }
    else if  (game->mov.m_lft == 1 && !wall_sx(game))
    {
        teta = game->pl.pov + M_PI/2;
        game->pl.pos_x -= cos(teta) * 0.1; //scambiati sen e cos
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
    // printf("%f\n", to_degrees(game->pl.pov));
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
    printf("fine deb\n\n\n");
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
    {
        game->mov.m_lft = 1;
        // double teta;

        // teta = game->pl.pov + M_PI/2;
        // game->pl.pos_x -= cos(teta) * 0.1; //scambiati sen e cos
        // game->pl.pos_y -= sin(teta) * 0.1;
    }
    if (keycode == KEY_D)// modified from "if" to "else if" (check if it is ok)
    {
        game->mov.m_rght = 1;
        // double teta;

        // teta = game->pl.pov + M_PI/2;
        // game->pl.pos_x += cos(teta) * 0.1;
        // game->pl.pos_y += sin(teta) * 0.1; //scambiati sen e cos
    }
    if (keycode == KEY_ESC)
        end_program(game);
    update_window(game); //commented cause I call update_window from mlx_loop_hook
    return (0);
}
