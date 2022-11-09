/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:11:58 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/09 16:43:55 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "parsing/parsing.h"

int main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!valid_arg(argc, argv[1]))
		return (-1);
	if (map_file_parse(argv[1], &game) == -1)
	{
		if (game.map)
			ft_free_char_mtx(game.map);
		return (-1);
	}
	if (game.map == NULL)
		return (-1);
	// if (main_function(&game) == -1)
	// 	return (-1);
	//game.tex.path = "bluestone.xpm";
    ft_init1(&game);
    ft_init2(&game);
    //update_window(&game);
    
    mlx_hook(game.screen.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
    mlx_loop_hook(game.screen.ptr, &update_window, &game);
    mlx_loop(game.screen.ptr);
	ft_free_char_mtx(game.map);
	return 0;
}
	