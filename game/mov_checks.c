/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:15:41 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/18 20:21:15 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int wall_f1(t_game *game)
{
    float test_x;
    float test_y;
    float f;

    f = 0;
    while (f < 0.4)
    {
        test_x = game->pl.pos_x + cos(game->pl.pov) * f;
        test_y = game->pl.pos_y + sin(game->pl.pov) * f;
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        f += 0.05;
    }
    return (0);
    // float test_x;
    // float test_y;
    // float test_a;

    // test_a = game->pl.pov - (3.14 /3);
    // while (test_a < (game->pl.pov + (3.14 /3)))
    // {
    //     test_x = game->pl.pos_x + 0.5 * cos(test_a);
    //     test_y = game->pl.pos_y + 0.5 * sin(test_a);
    //     if (game->map[(int)test_y][(int)test_x] == '1')
    //         return (1);
    //     test_a += 0.3;
    // }
    // return (0);
}

int wall_f2(t_game *game)
{
    float test_x;
    float test_y;
    float test_a;

    test_a = game->pl.pov - (3.14 /3);
    while (test_a < (game->pl.pov + (3.14 /3)))
    {
        test_x = game->pl.pos_x + 0.5 * cos(test_a);
        test_y = game->pl.pos_y + 0.5 * sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}

int wall_b(t_game *game)
{
    float test_x = game->pl.pos_x - cos(game->pl.pov) * 0.4;
    float test_y = game->pl.pos_y - sin(game->pl.pov) * 0.4;
     
    if (game->map[(int)test_y][(int)test_x] == '1')
             return (1);
    return (0);
    // float test_x;
    // float test_y;
    // float test_a;

    // test_a = 3.14 - game->pl.pov - (3.14 / 3);
    // while (test_a < (3.14 - game->pl.pov + (3.14 / 3)))
    // {
    //     test_x = game->pl.pos_x - 0.5 * cos(test_a);
    //     test_y = game->pl.pos_y - 0.5 * sin(test_a);
    //     if (game->map[(int)test_y][(int)test_x] == '1')
    //         return (1);
    //     test_a += 0.3;
    // }
    // return (0);
}

int wall_dx(t_game *game)
{
    float test_x;
    float test_y;
    float test_a;

    test_a = game->pl.pov + 3.14/2 - (3.14 /3);
    while (test_a < (game->pl.pov + 3.14/2 + (3.14 /3)))
    {
        test_x = game->pl.pos_x + 0.3 + cos(test_a);
        test_y = game->pl.pos_y + 0.3 + sin(test_a);
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

    test_a = game->pl.pov - 3.14/2 - (3.14 /3);
    while (test_a < (game->pl.pov - 3.14/2 + (3.14 /3)))
    {
        test_x = game->pl.pos_x + 0.3 + cos(test_a);
        test_y = game->pl.pos_y + 0.3  + sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}