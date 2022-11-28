/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:18:55 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/26 19:19:46 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* funzione che inizializza a zero i valori della struttura rc
*/
void	ft_init_rc(t_rc *rc)
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
* funzione che inizializza la mappa, la posizione 
* del giocatore e altre costanti del gioco;
*/
void	ft_init1(t_game *game)
{
	game->pl.pos_x += 0.5;
	game->pl.pos_y += 0.5;
	game->n_rays = W;
	game->delta_view = game->pl.view / game->n_rays;
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

void	ft_init_tex(t_game *game)
{
	game->no_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr,
			game->no_tex.path, &game->no_tex.width, &game->no_tex.height);
	game->no_tex.tex_addr = mlx_get_data_addr(game->no_tex.tex_img,
			&game->no_tex.bpp, &game->no_tex.size_line, &game->no_tex.endian);
	game->so_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr,
			game->so_tex.path, &game->so_tex.width, &game->so_tex.height);
	game->so_tex.tex_addr = mlx_get_data_addr(game->so_tex.tex_img,
			&game->so_tex.bpp, &game->so_tex.size_line, &game->so_tex.endian);
	game->ea_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr,
			game->ea_tex.path, &game->ea_tex.width, &game->ea_tex.height);
	game->ea_tex.tex_addr = mlx_get_data_addr(game->ea_tex.tex_img,
			&game->ea_tex.bpp, &game->ea_tex.size_line, &game->ea_tex.endian);
	game->we_tex.tex_img = mlx_xpm_file_to_image(game->screen.ptr,
			game->we_tex.path, &game->we_tex.width, &game->we_tex.height);
	game->we_tex.tex_addr = mlx_get_data_addr(game->we_tex.tex_img,
			&game->we_tex.bpp, &game->we_tex.size_line, &game->we_tex.endian);
}

void	ft_init2(t_game *game)
{
	t_screen	*screen;
	t_data		*img;

	screen = &game->screen;
	img = &game->screen.shown_img;
	screen->ptr = mlx_init();
	screen->win = mlx_new_window(screen->ptr, W, H, "prova");
	img->img = mlx_new_image(screen->ptr, W, H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_init_tex(game);
	time(&game->t_prev);
}
