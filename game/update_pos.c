/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:49:08 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/29 14:49:12 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_pos_f(t_game *game, double *x, double *y)
{
	*x += cos(game->pl.pov) * 0.2;
	*y += sin(game->pl.pov) * 0.2;
}

void	update_pos_b(t_game *game, double *x, double *y)
{
	*x -= cos(game->pl.pov) * 0.3;
	*y -= sin(game->pl.pov) * 0.3;
}

void	update_pos_sx(t_game *game, double *x, double *y)
{
	double	teta;

	teta = game->pl.pov + M_PI / 2;
	*x -= cos(teta) * 0.2;
	*y -= sin(teta) * 0.2;
}

void	update_pos_dx(t_game *game, double *x, double *y)
{
	double	teta;

	teta = game->pl.pov + M_PI / 2;
	*x += cos(teta) * 0.2;
	*y += sin(teta) * 0.2;
}

void	update_pos(t_game *game)
{
	double	pos_x;
	double	pos_y;

	pos_x = game->pl.pos_x;
	pos_y = game->pl.pos_y;
	if (game->mov.m_fwrd == 1)
		update_pos_f(game, &pos_x, &pos_y);
	else if (game->mov.m_bwrd == 1)
		update_pos_b(game, &pos_x, &pos_y);
	else if (game->mov.m_rght == 1)
		update_pos_dx(game, &pos_x, &pos_y);
	else if (game->mov.m_lft == 1)
		update_pos_sx(game, &pos_x, &pos_y);
	else if (game->mov.r_r == 1)
		game->pl.pov += H / 10000.00;
	else if (game->mov.r_l == 1)
		game->pl.pov -= H / 10000.00;
	collision(game, pos_x, pos_y);
}
