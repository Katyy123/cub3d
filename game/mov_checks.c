/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:15:41 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/21 13:25:37 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int wall_f1(t_game *game)
{
    double test_x;
    double test_y;
    double f;

    f = 0;
    while (f < 0.5)
    {
        test_x = game->pl.pos_x + 0.2 + cos(game->pl.pov) * f;
        test_y = game->pl.pos_y + 0.2 + sin(game->pl.pov) * f;
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        f += 0.05;
    }
    return (0);
}

int wall_f2(t_game *game)
{
    double test_x;
    double test_y;
    double test_a;

    test_a = game->pl.pov - (M_PI /4);
    while (test_a < (game->pl.pov + (M_PI /4)))
    {
        test_x = game->pl.pos_x + 0.5 * cos(test_a);
        test_y = game->pl.pos_y + 0.5 * sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}

int wall_b1(t_game *game)
{
    double test_x;
    double test_y;
    double f;

    test_x = game->pl.pos_x - 0.5 * (cos(game->pl.pov) + 0.1);
    test_y = game->pl.pos_y - 0.5 * (sin(game->pl.pov) + 0.1);
    f = 0;
    while (f < 0.4)
    {
        test_x = game->pl.pos_x - cos(game->pl.pov) * f;
        test_y = game->pl.pos_y - sin(game->pl.pov) * f;
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        f += 0.05;
    }
    return (0);
}

int wall_b2(t_game *game)
{
    double test_x;
    double test_y;
    double test_a;

    test_a = M_PI - game->pl.pov - (M_PI / 8);
    while (test_a < (M_PI - game->pl.pov + (M_PI / 8)))
    {
        test_x = game->pl.pos_x - 0.5 * cos(test_a);
        test_y = game->pl.pos_y - 0.5 * sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}

int wall_dx(t_game *game)
{
    double test_x;
    double test_y;
    double test_a;

    test_a = game->pl.pov + M_PI/2 - (M_PI /3);
    while (test_a < (game->pl.pov + M_PI/2 + (M_PI /3)))
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
    double test_x;
    double test_y;
    double test_a;

    test_a = game->pl.pov - M_PI/2 - (M_PI /3);
    while (test_a < (game->pl.pov - M_PI/2 + (M_PI /3)))
    {
        test_x = game->pl.pos_x + 0.3 + cos(test_a);
        test_y = game->pl.pos_y + 0.3  + sin(test_a);
        if (game->map[(int)test_y][(int)test_x] == '1')
            return (1);
        test_a += 0.3;
    }
    return (0);
}