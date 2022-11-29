/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:30:26 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/28 18:41:13 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* check if a pixel of a wall has to be shown in the minimap */
t_bool	is_pix_in_minimap(t_game *game, int x, int y)
{
	t_minimap	*m_map;

	m_map = &game->m_map;
	if (x >= m_map->start_l && x <= m_map->end_r
		&& y >= m_map->start_up && y <= m_map->end_d)
		return (TRUE);
	return (FALSE);
}

/* check if a tile of the map has to be shown in the minimap */
t_bool	is_tile_in_minimap(t_game *game, int x, int y)
{
	int				map_width;
	double			half_tiles;
	t_double_coo	pl;
	t_minimap		*m_map;

	m_map = &game->m_map;
	pl.x = game->pl.pos_x;
	pl.y = game->pl.pos_y;
	map_width = m_map->end_r - m_map->start_l;
	half_tiles = map_width / m_map->tile_width / 2;
	if (x + 1 >= (int)(pl.x - half_tiles) && x - 1 < pl.x + half_tiles
		&& y + 1 >= (int)(pl.y - half_tiles) && y - 1 < pl.y + half_tiles)
		return (TRUE);
	return (FALSE);
}

/* check if a pixel has to belong to the circle
representing the player in the minimap */
t_bool	is_inside_circle(t_game *game, t_coord point, t_coord ctr, int radius)
{
	t_minimap	*m_map;
	float		dist;

	m_map = &game->m_map;
	dist = sqrtf(powf(point.x - ctr.x, 2.) + powf(point.y - ctr.y, 2.));
	if (dist <= radius)
		return (TRUE);
	return (FALSE);
}

t_coord	coord_to_point(int x, int y)
{
	t_coord	point;

	point.x = x;
	point.y = y;
	return (point);
}
