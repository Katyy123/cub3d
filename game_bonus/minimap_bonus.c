/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:29:28 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/28 18:37:10 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* draw a single wall in the minimap */
void	draw_wall(t_game *game, int tile_x, int tile_y)
{
	int				x;
	int				y;
	t_double_coo	dist_pl_tile_pix;
	t_screen		*screen;
	t_minimap		*m_map;

	screen = &game->screen;
	m_map = &game->m_map;
	dist_pl_tile_pix.x = (game->pl.pos_x - tile_x) * m_map->tile_width;
	dist_pl_tile_pix.y = (game->pl.pos_y - tile_y) * m_map->tile_width;
	y = m_map->ctr.y - dist_pl_tile_pix.y;
	while (y < m_map->ctr.y - dist_pl_tile_pix.y + m_map->tile_width)
	{
		x = m_map->ctr.x - dist_pl_tile_pix.x;
		while (x < m_map->ctr.x - dist_pl_tile_pix.x + m_map->tile_width)
		{
			if (is_pix_in_minimap(game, x, y) == TRUE)
				my_mlx_pixel_put(&screen->shown_img, x, y, MAP_WALL_COL);
			x++;
		}
		y++;
	}
}

/* draw the little circle in front of the player,
to indicate the point of view */
void	draw_pl_dir(t_game *game)
{
	t_screen	*screen;
	t_minimap	*m_map;
	int			x;
	int			y;
	t_coord		point;

	screen = &game->screen;
	m_map = &game->m_map;
	m_map->dir_ctr.x = m_map->ctr.x + m_map->dist_pl_dir * cos(game->pl.pov);
	m_map->dir_ctr.y = m_map->ctr.y + m_map->dist_pl_dir * sin(game->pl.pov);
	y = m_map->dir_ctr.y - (m_map->pl_dir_width / 2);
	while (y < m_map->dir_ctr.y + (m_map->pl_dir_width / 2))
	{
		x = m_map->dir_ctr.x - (m_map->pl_dir_width / 2);
		while (x < m_map->dir_ctr.x + (m_map->pl_dir_width / 2))
		{
			point = coord_to_point(x, y);
			if (is_inside_circle(game, point, m_map->dir_ctr,
					(m_map->pl_dir_width) / 2) == TRUE)
				my_mlx_pixel_put(&screen->shown_img, x, y, MAP_PL_DIR_COL);
			x++;
		}
		y++;
	}
}

/* draw the player in the minimap as a circle*/
void	draw_player(t_game *game)
{
	t_screen	*screen;
	t_minimap	*m_map;
	int			x;
	int			y;
	t_coord		point;

	screen = &game->screen;
	m_map = &game->m_map;
	y = m_map->ctr.y - (m_map->pl_width / 2);
	while (y < m_map->ctr.y + (m_map->pl_width / 2))
	{
		x = m_map->ctr.x - (m_map->pl_width / 2);
		while (x < m_map->ctr.x + (m_map->pl_width / 2))
		{
			point = coord_to_point(x, y);
			if (is_inside_circle(game, point, m_map->ctr,
					(m_map->pl_width) / 2) == TRUE)
				my_mlx_pixel_put(&screen->shown_img, x, y, MAP_PLAYER_COL);
			x++;
		}
		y++;
	}
	draw_pl_dir(game);
}

/* draw the minimap in a square in the down right-hand side of the window */
void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	init_minimap(game);
	draw_border(game);
	draw_background(game);
	y = 0;
	while (y < game->map_y)
	{
		x = 0;
		while (x < game->map_x)
		{
			if (is_tile_in_minimap(game, x, y) == TRUE)
			{
				if (game->map[y][x] == '1')
					draw_wall(game, x, y);
			}
			x++;
		}
		y++;
	}
	draw_player(game);
}
