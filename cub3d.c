
#include "inc/cub3d.h"
#define H 1080
#define W 1920



//provv
int     find_texture(char *buff)
{
    if (!ft_strncmp(buff, "N", 1))
        return (1);
    if (!ft_strncmp(buff, "S", 1))
        return (2);
    if (!ft_strncmp(buff, "W", 1))
        return (3);
    if (!ft_strncmp(buff, "E", 1))
        return (4);
    else
        return (0);
}
//aggiungere gestione dell'errore se il file della texture non è valido
int     save_texture(int nswe, char *line)// t_game *game)
{
    char **str;
    str = ft_split(line, ' ');
    if (nswe == 1)
        printf("trovato NO\n");
    else if (nswe == 2)
        printf("trovato SO\n");
    else if (nswe == 3)
        printf("trovato WE\n");
    else if (nswe == 4)
        printf("trovato EA\n");
    else
        return (0);
    //ft_free(str); da scrivere funzione che libera array di strighe
    return (1);
}
//provv
int     parser(char *file, t_game *game)
{
    int     i;
    int     fd;
    char    *buff;

    i = 0;
    (void)game;
    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("file not found\n");
        return (1);
    }
    buff = get_next_line(fd); //con gnl basta liberare alla fine??
    
    
    while(buff && i < 4)
    {
       
        //if (ft_strlen(buff) > 0 && buff[ft_strlen(buff) - 1] == '\n')   //sostituisco l'accapo in ogni linea con un terminatore
        //    buff[ft_strlen(buff) - 1] = '\0';
        //da gestire eventuali spazi a inizio riga!!
        if (save_texture(find_texture(buff), buff) != 0)
            i++;
        
        printf("%s\n", buff);
        buff = get_next_line(fd);
          
    }
    if (!buff)
    {
        printf("info insufficienti nel file\n");
        return (1);
    }
    //conto righe nella mappa
    game->map_y = 0;
    game->map_y = 0;
    while(buff)
    {
        game->map[game->map_y] = ft_strdup(buff);
        game->map_y++;
        buff = get_next_line(fd);
    }
    return (0);
}
//provv
int     arg_check(int ac, char **av)
{
    char *error;
    
    error = NULL;
    if(ac != 2)
        error = "Error: wrong arguments number\n";
    else
        if(ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
            error = "Error: invalid file extension\n";
    if (error)
    {
        write(2, error, ft_strlen(error));
        return (1);
    }
    return (0);
}
//provv


void    ft_init(t_game *game)
{
    game->pl.pos_x = 10;
    game->pl.pos_y = 6;     //inizialmente il giocatore è in un punto deciso da me
    game->pl.view = 3.14/3;
    game->pl.pov = 3.14;
    game->delta_view = game->pl.view/W;
    game->n_rays = W;
    game->game_ended = 0;
    int i = 0;
    int j;
    int n = 0;
    while (i <= game->map_y)
    {
        j = 0;
        while (j < ft_strlen(game->map[i]) - 1)
        {
            game->lmap[n] = game->map[i][j];
            j++;
            n++;
        }
        //printf("%s", game->map[i]);
        i++;
    }
    printf("%s\n", game->lmap);

}

/*
t_window	ft_new_window(void *mlx, int widht, int height, char *name)
{
	t_window	window;

	window.reference = mlx_new_window(mlx, widht, height, name);
	window.size.x = widht;
	window.size.y = height;
	mlx_hook(window.reference, 17, 0, ft_close, 0);
	return (window);
}
*/

/*
* funzione per scrivere pixel nell'immagine
* gli passo la struttura img, la posizio x, y del pixel e il colore!!
* nota bene: int offset = (y * line_length + x * (bits_per_pixel / 8)); per calcolare la posizione in cui scrivo!
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void pixel_col_put(t_data *data, int x, int y, int color, int pxnum)
{
    int i;

    i = 0;
    while (i < pxnum)
    {
        my_mlx_pixel_put(data, x, y, color);
        i++;
        y++;
    }
}


/*
* funzione che stabilisce se la parete è stata colpita
int wall_enountered(t_game *game, float d)
{

}
*/


/*
* funzione che calcola la distanza dell' ostacolo dall'osservatore per ogni raggio della visuale
*/
float get_distance(t_game *game, int w)
{
    int wall_enountered = 0;
    float d;
    float ray_a;
    float eye_x;
    float eye_y;
    int ntest_x;// = (int)(posX + distance_to_wall * cos(f_ray_angle))
    int ntest_y; // = (int)(posY + distance_to_wall * sen(f_ray_angle))

    d = 0;
    ray_a = game->pl.pov - game->pl.view/2 + game->delta_view * w;
    printf("ray dellángolo %f\n", ray_a);
    while (wall_enountered == 0)
    {
        //printf("loop1\n");
        d += 0.1;
        eye_x = d * sin(ray_a);
        eye_y = d * cos(ray_a);
        ntest_x = game->pl.pos_x + eye_x;
        ntest_y = game->pl.pos_y + eye_y;
        //printf("char: %c", game->lmap[ntest_y * game->map_x + ntest_y]);
        //printf("char: map[%d][%d] = %c",ntest_x, ntest_y, game->map[ntest_x][ntest_y]);        
        if (game->map[ntest_y][ntest_x] == '1')
            break;   
    }
     //printf("elapsed distance: %f\n", d);
    return d;
}


/*
*
*/
void create_immage(t_game *game, t_data *img)
{
    int i;
    float d;
    float celing = 0;
    //float wall = 0;
    //float floor = 0;

    i = 0;
    while (i < W) //disegno una linea per ogni colonna di pixel della finestra
    {
        d = get_distance(game, i);
        //printf("\n\n!!!!!!  d=%f      !!!!!!!!!!\n\n", d);
        celing = H/2 - H/d;
        //floor = H - celing;
        pixel_col_put(img, i, 0, 0x00FF0000, celing);
        i++;
    }
    printf("primo angolo:%f\n",game->pl.pov - game->pl.view/2);
    
}

int	ft_launch_game(t_game *game)
{
    t_data	img; //struttura dove salvo le info dellímmagine che mi servono per scriverci i pixel dentro
    void	*mlx;
	void	*mlx_win;
    
	(void) game;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, W, H, "Hello world!"); //inizializzo finestra
    img.img = mlx_new_image(mlx, W, H);  //inizializzo immagine, grande come líntera finestra
    /*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);


    create_immage(game, &img);
    //pixel_col_put(&img, 5, 5, 0x00FF0000, 10);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);

	return (0);
}

int main(int ac, char **av)
{
    t_game *game;

    game = (t_game *)malloc(sizeof(t_game));
    if (arg_check(ac, av))
        ft_close();
    if (parser(av[1], game))
        ft_close();
    //int i = 0;
    /*
    while (i <= game->map_y)
    {
        printf("%s", game->map[i]);
        i++;
    }
    */  
    ft_init(game);
    ft_launch_game(game);
    
    return (0);
}

