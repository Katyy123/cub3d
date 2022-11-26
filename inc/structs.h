/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:39:40 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/26 17:14:57 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef STRUCTS_H
# define STRUCTS_H

#define H 1080
#define W 1920
#define X 0
#define Y 1

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

/* struct for the int coordinates of a point */
typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

/* struct for the double coordinates of a point */
typedef struct s_double_coord
{
	double	x;
	double	y;
}	t_double_coo;

/* struct for the minimap:
bd_start_up: beginning of the boarder on top of the minimap
bd_start_l: beginning of the boarder on the left
bd_end_d: end of the boarder down
bd_end_r: end of the boarder on the right
start_up: beginning of the minimap from the top
start_l: beginning of the minimap from the left
end_d: end of the minimap down
end_r: end of the minimap on the right
ctr_x: x_coordinate of the minimap center 
ctr_y: y_coordinate of the minimap center */
typedef struct s_minimap
{
	int	bd_width;
	int	tile_width;
	int	pl_width;
	int	dist_win;
	int	bd_start_up;
	int	bd_start_l;
	int	bd_end_d;
	int	bd_end_r;
	int	start_up;
	int	start_l;
	int	end_d;
	int	end_r;
	int	ctr_x;
	int	ctr_y;
}	t_minimap;


/*
* struttura necessaria a gestire le immagini con minilibx.
* contiene il puntatore a immagine img;
* gli altri elementi servono a [...]
*/
typedef struct s_data {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


//aggiunta da casa, da testare
typedef struct s_rc {
	int ntest_x;// = (int)(posX + distance_to_wall * cos(f_ray_angle))
    int ntest_y; // = (int)(posY + distance_to_wall * sen(f_ray_angle)
    
    //per il calcolo del quadrante
    double mid_block_x;
    double mid_block_y;
    double test_point_x;
    double test_point_y;
    double test_angle;
}				t_rc;

typedef struct s_mov {
	int		m_fwrd;
	int		m_bwrd;
	int		m_lft;
	int		m_rght;
	int		r_l;
	int		r_r;
}				t_mov;

/*
* struttura in cui vengono salvate le path alle 4 diverse textures
*/
typedef struct s_tex
{
	char	*path;
	void	*tex_img;
	void	*tex_addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;

/*
* struct where floor and ceiling colors are saved
*/

typedef struct s_col
{
	int	f_col;
	int	c_col;
}	t_col;

/*
* struttura che contiene:
* pos_x = cordinata x del giocatore nella mappa
* pos_y = cordinata y del giocatore nella mappa
* view = valore del campo visivo del giocatore
* pov = direzione dello sguardo
*/
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	view;
	double	pov;
}	t_player;

/*
* struttura che contiene elementi utili alla gestione della finestra di gioco
* ptr è il pointer da inizializzare con mlx_init()
* win è il pointer alla finestra, da inizializzare con mlx_new_window(...)
* shown_img è l'immagine mostrata sulla fienstra, che viene refreshata a ogni loop
*/
typedef struct s_screen
{
	int			orient;
	void		*ptr;
	void		*win;
	t_data		shown_img;
}				t_screen;

typedef struct s_rproperties
{
	double		m;
    double		sx;
    double		sy;
    double		cos_a;
    double		sin_a;
}				t_rproperties;

typedef struct s_game
{
	char		buffer[H];
	t_rc		r;
	t_screen	screen;
	t_player	pl;
	t_tex		no_tex;
	t_tex		so_tex;
	t_tex		we_tex;
	t_tex		ea_tex;
	t_col		col;
	t_mov		mov;
	int			screen_x;
	int			screen_y;
	int			map_x;
	int			map_y;
	double		n_rays; // = screen_x
	double		delta_view;
	double		f_sample_x;
	int			game_ended;
	char		**map;
	char		nsoe;
	t_rproperties	ray;
	time_t		t_prev;
	t_minimap	m_map;
}	t_game;

#endif