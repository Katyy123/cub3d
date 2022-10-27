/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:01:01 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/10/26 02:30:59 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
} t_textures;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	view;
	float	pov;
} t_player;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game
{
	char		*map[100];	//matrice della mappa in due dimensioni
	char		lmap[10000];	//array della mappa linearizzata
	t_player	pl;
	t_textures	textures;
	int			screen_x;
	int			screen_y;
	int			map_x;
	int			map_y;
	float		n_rays; // = screen_x
	float		delta_view;
	int			game_ended;
//	t_strutt	s;
} t_game;

#endif

void	*mlx;
	void	*mlx_win;
	t_data	img;

	/*
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	*/