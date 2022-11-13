/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:01:01 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/11/13 11:03:41 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

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
	float	pos_x;
	float	pos_y;
	float	view;
	float	pov;
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

typedef struct s_game
{
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
	float		n_rays; // = screen_x
	float		delta_view;
	float		f_sample_x;
	int			game_ended;
	char		**map;
}	t_game;

#endif