/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:22:38 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/28 19:07:20 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_orient(t_game *game, double cos_a, double sin_a, char xy)
{
	if (cos_a > 0 && sin_a > 0)
		set_no(game, xy);
	else if (cos_a > 0 && sin_a < 0)
		set_so(game, xy);
	else if (cos_a < 0 && sin_a > 0)
		set_ne(game, xy);
	else
		set_se(game, xy);
}

/*
* determins where the wall detected is facing
*/
void	get_orient(t_game *game)
{
	double	test_angle;

	test_angle = game->r.test_angle;
	if (test_angle >= -M_PI * 0.25 && test_angle < M_PI * 0.25)
	{
		game->screen.orient = 1;
	}
	if (test_angle >= M_PI * 0.25 && test_angle < M_PI * 0.75)
	{
		game->screen.orient = 2;
	}
	if (test_angle < -M_PI * 0.25f && test_angle >= -M_PI * 0.75)
	{
		game->screen.orient = 3;
	}
	if (test_angle >= M_PI * 0.75f || test_angle < -M_PI * 0.75)
	{
		game->screen.orient = 4;
	}
}

/*
* color sampling from texture
*/
int	get_color(t_game *game, int y, int wall_h, t_tex tex)
{
	int	color;
	int	yt;
	int	xt;
	int	xpx;

	xpx = tex.width;
	yt = (int)((double)y / wall_h * tex.height);
	xt = (int)(game->f_sample_x * tex.width);
	color = (*(int *)(tex.tex_addr + (4 * xpx * yt) + (4 * xt)));
	return (color);
}

t_tex	ret_right_tex(t_game *game)
{
	char	orient;

	orient = game->nsoe;
	if (orient == 'N')
		return (game->no_tex);
	if (orient == 'S')
		return (game->so_tex);
	if (orient == 'E')
		return (game->ea_tex);
	if (orient == 'W')
		return (game->we_tex);
	else
		return (game->we_tex);
}
