/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:31:37 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/17 19:36:24 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	end_program(t_game *game) //to check if I need to free images and other stuff
{
	mlx_destroy_window(game->screen.ptr, game->screen.win);
	mlx_destroy_image(game->screen.ptr, game->screen.shown_img.img);
	free(game->screen.ptr);
	ft_free_char_mtx(game->map);
	free(game->no_tex.path);
	free(game->so_tex.path);
	free(game->we_tex.path);
	free(game->ea_tex.path);
	exit(0);
}
