/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:11:58 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/30 18:27:19 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "map/map.h"

int main(int argc, char **argv)
{
	t_game	game;

	if (!valid_arg(argc, argv[1]))
		return (-1);
	game.map = map_file_parse(argv[1], &game);
	return 0;
}
	