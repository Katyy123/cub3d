/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 19:03:37 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/26 19:37:17 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	first_step(t_game *game, int *eye, int *step, double *ip)
{
	eye[X] = game->pl.pos_x;
	eye[Y] = game->pl.pos_y;
	if (game->ray.cos_a < 0)
	{
		step[X] = -1;
		ip[X] = (game->pl.pos_x - (double)eye[X]) * game->ray.sx;
	}
	else
	{
		step[X] = 1;
		ip[X] = (((double)eye[X] + 1) - game->pl.pos_x) * game->ray.sx;
	}
	if (game->ray.sin_a < 0)
	{
		step[Y] = -1;
		ip[Y] = (game->pl.pos_y - (double)eye[Y]) * game->ray.sy;
	}
	else
	{
		step[Y] = 1;
		ip[Y] = (((double)eye[Y] + 1) - game->pl.pos_y) * game->ray.sy;
	}
}

/*
* incrementa di una tile lungo x, aggiorna la distanza e controlla se cé il muro
*/
t_bool	increment_x(t_game *game, int *step, int *eye, double *ip)
{
	t_bool	wall;

	wall = FALSE;
	eye[X] += step[X];
	if (!(game->map[eye[Y]][eye[X]] == '1'))
	{
		ip[X] += game->ray.sx;
		game->d = ip[X];
		game->f_sample_x = (game->pl.pos_y + game->d * game->ray.sin_a)
			- (int)(game->pl.pos_y + game->d * game->ray.sin_a);
	}
	else
	{
		wall = TRUE;
		game->d = ip[X];
		game->f_sample_x = (game->pl.pos_y + game->d * game->ray.sin_a)
			- (int)(game->pl.pos_y + game->d * game->ray.sin_a);
		set_orient(game, game->ray.cos_a, game->ray.sin_a, 'y');
	}
	return (wall);
}

/*
* incrementa di una tile lungo y, aggiorna la distanza e controlla se cé il muro
*/
t_bool	increment_y(t_game *game, int *step, int *eye, double *ip)
{
	t_bool	wall;

	wall = FALSE;
	eye[Y] += step[Y];
	if (!(game->map[eye[Y]][eye[X]] == '1'))
	{
		ip[Y] += game->ray.sy;
		game->d = ip[Y];
		game->f_sample_x = (game->pl.pos_x + game->d * game->ray.cos_a)
			- (int)(game->pl.pos_x + game->d * game->ray.cos_a);
	}
	else
	{
		wall = TRUE;
		game->d = ip[Y];
		game->f_sample_x = (game->pl.pos_x + game->d * game->ray.cos_a)
			- (int)(game->pl.pos_x + game->d * game->ray.cos_a);
		set_orient(game, game->ray.cos_a, game->ray.sin_a, 'x');
	}
	return (wall);
}

/*
* funzione che scrive in d la distanza dal muro con dda
*/
void	increment_d(t_game *game, int *step, int *eye, double *ip)
{
	t_bool	wall;

	wall = FALSE;
	first_step(game, eye, step, ip);
	while (!wall)
	{
		if (ip[X] >= ip[Y])
			wall = increment_y(game, step, eye, ip);
		else
			wall = increment_x(game, step, eye, ip);
	}
}

/*
* funzione che calcola la distanza dell' ostacolo dall'osservatore 
* per ogni raggio della visuale
*/
double	get_distance(t_game *game, int w)
{
	double	ray_a;
	int		step[2];
	int		eye[2];
	double	ip[2];

	game->d = 0;
	ray_a = game->pl.pov - game->pl.view / 2 + game->delta_view * w;
	game->ray.m = tan(ray_a);
	game->ray.sx = sqrt(1 + game->ray.m * game->ray.m);
	game->ray.sy = sqrt(1 + (1 / game->ray.m) * (1 / game->ray.m));
	game->ray.cos_a = cos(ray_a);
	game->ray.sin_a = sin(ray_a);
	increment_d(game, step, eye, ip);
	return (game->d);
}
