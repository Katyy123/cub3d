/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:51:56 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/28 19:08:26 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_no(t_game *game, char xy)
{
	if (xy == 'x')
	{
		game->nsoe = 'N';
	}
	else
	{
		game->nsoe = 'O';
	}
}

void	set_so(t_game *game, char xy)
{
	if (xy == 'x')
			game->nsoe = 'S';
	else
		game->nsoe = 'O';
}

void	set_ne(t_game *game, char xy)
{
	if (xy == 'x')
			game->nsoe = 'N';
	else
		game->nsoe = 'E';
}

void	set_se(t_game *game, char xy)
{
	if (xy == 'x')
	{
		game->nsoe = 'S';
	}
	else
	{
		game->nsoe = 'E';
	}
}
