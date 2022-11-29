/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:10:59 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/28 19:28:16 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_mlx_functions(t_game *game)
{
	mlx_hook(game->screen.win, X_EVENT_KEY_RELEASE, 0, &key_rlease, game);
	mlx_hook(game->screen.win, X_EVENT_KEY_PRESS, 0, &key_press, game);
	mlx_hook(game->screen.win, X_EVENT_MOUSE_PRESS, 1L << 0, get_mouse, game);
	mlx_hook(game->screen.win, X_EVENT_MOUSE_MOVE, 1L << 0, trasl_mov, game);
	mlx_hook(game->screen.win, X_EVENT_MOUSE_RELEASE,
		1L << 0, unlock_mouse, game);
	mlx_hook(game->screen.win, X_EVENT_EXIT, 0, end_program, game);
	mlx_loop_hook(game->screen.ptr, &update_window, game);
	mlx_loop(game->screen.ptr);
}
