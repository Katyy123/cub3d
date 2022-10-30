/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:01:01 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/10/30 14:09:20 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


/*
* struttura necessaria a gestire le immagini con minilibx.
* contiene il puntatore a immagine img;
* gli altri elementi servono a [...]
*/
typedef struct	s_data {
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

/*
* struttura in cui vengono salvate le path alle 4 diverse textures
*/
typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
} t_textures;

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
} t_player;

/*
* struttura che contiene elementi utili alla gestione della finestra di gioco
* ptr è il pointer da inizializzare con mlx_init()
* win è il pointer alla finestra, da inizializzare con mlx_new_window(...)
* shown_img è l'immagine mostrata sulla fienstra, che viene refreshata a ogni loop
*/
typedef	struct	s_screen
{
	void		*ptr;
	void		*win;
	t_data		shown_img;
}				t_screen;

typedef struct s_game
{
    t_screen	screen;
	t_player	pl;
	t_textures	textures;
	int			screen_x;
	int			screen_y;
	int			map_x;
	int			map_y;
	float		n_rays; // = screen_x
	float		delta_view;
	int			game_ended;
    char		**map;
    //char		lmap;	//array della mappa linearizzata
	

} t_game;

#endif