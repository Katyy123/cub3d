/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:26:03 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/21 20:11:22 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	calc_distance(t_game *game, double ray_a, t_coord point)
{
	double	d;
	
	d = abs((int)(game->pl.pos_x - point.x)) / cos(ray_a);
	return (d);
}

t_coord	find_1st_horiz_inters(t_game *game, double ray_a)
{
	t_coord	point;

	if (sin(ray_a) < 0)
		point.y = (int)game->pl.pos_y - 0.001;
	else
		point.y = (int)game->pl.pos_y + 1;
	point.x = game->pl.pos_x + (game->pl.pos_y - point.y) / tan(ray_a);
	return (point);
}

double	dist_horiz_inters(t_game *game, double ray_a)
{
	t_coord	point;
	double	xa;
	double	ya;
	
	point = find_1st_horiz_inters(game, ray_a);
	printf("point.x = %f, point.y = %f\n", point.x, point.y);
	printf("(int)point.x = %d  (int)point.y = %d\n", (int)point.x, (int)point.y);
	if (game->map[(int)point.x][(int)point.y] == '1')
		return (calc_distance(game, ray_a, point));
	if (sin(ray_a) < 0)
		ya = -1;
	else
		ya = 1;
	xa = abs((int)ya) / tan(ray_a);
	while (point.x <= game->map_x && point.y <= game->map_y)
	{
		if (game->map[(int)point.x][(int)point.y] == '1')
			return (calc_distance(game, ray_a, point));
		point.x += xa;
		point.y += ya;
	}
	return (0);
}

t_coord	find_1st_vert_inters(t_game *game, double ray_a)
{
	t_coord	point;

	if (cos(ray_a) < 0)
		point.y = (int)game->pl.pos_y - 0.001;
	else
		point.y = (int)game->pl.pos_y + 1;
	point.x = game->pl.pos_x + (game->pl.pos_y - point.y) / tan(ray_a);
	return (point);
}

double	dist_vert_inters(t_game *game, double ray_a)
{
	t_coord	point;
	double	xa;
	double	ya;
	
	point = find_1st_vert_inters(game, ray_a);
	if (game->map[(int)point.x][(int)point.y] == '1')
		return (calc_distance(game, ray_a, point));
	if (cos(ray_a) < 0)
		xa = -1;
	else
		xa = 1;
	ya = abs((int)xa) * tan(ray_a);
	while (point.x <= game->map_x && point.y <= game->map_y)
	{
		if (game->map[(int)point.x][(int)point.y] == '1')
			return (calc_distance(game, ray_a, point));
		point.x += xa;
		point.y += ya;
	}
	return (0);
}

double get_distance(t_game *game, int w)
{
    double	d;
	double	d_horiz;
	double	d_vert;
    double	ray_a;
    //t_bool  wall;
    
    //wall = FALSE;
    d = 0;
    ray_a =  game->pl.pov - game->pl.view/2 + game->delta_view * w; //ricontrollare questa
    //while (!wall)
	//wall = increment_d(&d, game, ray_a);

  
	d_horiz = dist_horiz_inters(game, ray_a);
	d_vert = dist_vert_inters(game, ray_a);
	if (d_horiz < d_vert)
		d = d_horiz;
	else
		d = d_vert;


    if (w > W/2 - 40 && w < W/2 + 40)
        printf("ray_a = %f => d = %f\t cos_a = %f sin_a = %f\n ", to_degrees(ray_a), d, cos(ray_a), sin(ray_a));
    //calcolo il quadrante:
    game->r.mid_block_x = (double) game->r.ntest_x + 0.5; 
    game->r.mid_block_y = (double) game->r.ntest_y + 0.5;

    game->r.test_angle = 1000;
    game->r.test_angle = atan2f((game->r.test_point_y - game->r.mid_block_y),
                                 (game->r.test_point_x - game->r.mid_block_x));
    get_orient(game);


    return d;

}