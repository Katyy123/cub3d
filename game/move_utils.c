/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:49:08 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/26 20:09:04 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	collision(t_game *game, double pos_x, double pos_y)
{
	double	r;
	double	a;

	r = 0.25;
	a = game->pl.pov;
	if (game->map[(int)(pos_y
			+ (r * sin(a)))][(int)(pos_x + (r * cos(a)))] == '1')
		return ;
	r = 0.25;
	a = 0.0;
	while (a <= 2 * M_PI)
	{
		if (game->map[(int)(pos_y
				+ (r * sin(a)))][(int)(pos_x + (r * cos(a)))] == '1')
			return ;
		a += 0.1;
	}
	game->pl.pos_x = pos_x;
	game->pl.pos_y = pos_y;
}

int	key_rlease(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->mov.m_fwrd = 0;
	if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->mov.m_bwrd = 0;
	if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->mov.r_r = 0;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->mov.r_l = 0;
	if (keycode == KEY_A)
		game->mov.m_lft = 0;
	if (keycode == KEY_D)
		game->mov.m_rght = 0;
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->mov.m_fwrd = 1;
	if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->mov.m_bwrd = 1;
	if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->mov.r_r = 1;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->mov.r_l = 1;
	if (keycode == KEY_A)
		game->mov.m_lft = 1;
	if (keycode == KEY_D)
		game->mov.m_rght = 1;
	if (keycode == KEY_ESC)
		end_program(game);
	update_window(game);
	return (0);
}
