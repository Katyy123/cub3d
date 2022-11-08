/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:11:58 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/08 20:45:39 by cfiliber         ###   ########.fr       */
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
	if (main_function(&game) == -1)
		return (-1);
	ft_free_char_mtx(game.map);
	return 0;
}
	