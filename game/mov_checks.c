/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:15:41 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/17 18:51:20 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int wall_f(t_game *game)
{
    float test_x;
    float test_y;
    float test_a;

    test_a = game->pl.pov - (3.14 /4);
    while (test_a < (game->pl.pov + (3.14 /4)))
    {
        test_x = game->pl.pos_x + cos(test_a);
        test_y = game->pl.pos_y + sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}

int wall_b(t_game *game)
{
    float test_x;
    float test_y;
    float test_a;

    test_a = 3.14 - game->pl.pov - (3.14 /4);
    while (test_a < (3.14 - game->pl.pov + (3.14 /4)))
    {
        test_x = game->pl.pos_x - cos(test_a);
        test_y = game->pl.pos_y - sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}

int wall_dx(t_game *game)
{
    float test_x;
    float test_y;
    float test_a;

    test_a = game->pl.pov + 3.14/2 - (3.14 /4);
    while (test_a < (game->pl.pov + 3.14/2 + (3.14 /4)))
    {
        test_x = game->pl.pos_x + cos(test_a);
        test_y = game->pl.pos_y + sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}

int wall_sx(t_game *game)
{
    float test_x;
    float test_y;
    float test_a;

    test_a = game->pl.pov - 3.14/2 - (3.14 /4);
    while (test_a < (game->pl.pov - 3.14/2 + (3.14 /4)))
    {
        test_x = game->pl.pos_x + cos(test_a);
        test_y = game->pl.pos_y + sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}