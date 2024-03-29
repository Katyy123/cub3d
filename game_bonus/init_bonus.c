/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:18:55 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/29 16:15:26 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* initialize t_minimap struct */
void	init_minimap(t_game *game)
{
	t_minimap	*m_map;

	m_map = &game->m_map;
	m_map->bd_width = W / 300;
	m_map->tile_width = W / 90;
	m_map->pl_width = W / 110;
	m_map->pl_dir_width = m_map->pl_width / 2;
	m_map->dist_pl_dir = sqrtf(2) * m_map->pl_width / 2
		+ m_map->pl_dir_width / 2;
	m_map->dist_win = 10 + W / 96;
	m_map->bd_start_l = 4 * W / 5;
	m_map->bd_start_up = H - (W - m_map->bd_start_l);
	m_map->bd_end_d = H - m_map->dist_win;
	m_map->bd_end_r = W - m_map->dist_win;
	m_map->start_up = m_map->bd_start_up + m_map->bd_width;
	m_map->start_l = m_map->bd_start_l + m_map->bd_width;
	m_map->end_d = m_map->bd_end_d - m_map->bd_width;
	m_map->end_r = m_map->bd_end_r - m_map->bd_width;
	m_map->ctr.x = (m_map->start_l + (W - m_map->dist_win)) / 2;
	m_map->ctr.y = (m_map->start_up + (H - m_map->dist_win)) / 2;
}

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
	game->test_angle = 0;
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
	screen->win = mlx_new_window(screen->ptr, W, H,
			"cub3D made by Catia Filiberto and Tommaso Bertolini");
	img->img = mlx_new_image(screen->ptr, W, H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	ft_init_tex(game);
}
