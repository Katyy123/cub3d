/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:40:24 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/29 19:17:16 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 10 && x < (W - 10) && y > 10 && y < (H - 10))
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	draw_ceiling(t_game *game, double ceiling_h, int line)
{
	t_screen	*screen;
	int			y;

	y = 0;
	screen = &game->screen;
	while (y < ceiling_h)
	{
		my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.c_col);
		y++;
	}
	return (y);
}

/*
* draws one line per ray on the screen
*/
void	draw_line(t_screen *screen, int line, double ceiling_h, t_game *game)
{
	double	floor_h;
	double	wall_h;
	int		y;

	floor_h = ceiling_h;
	wall_h = H - ceiling_h - floor_h;
	y = draw_ceiling(game, ceiling_h, line);
	while (y < ceiling_h + wall_h)
	{
		my_mlx_pixel_put(&screen->shown_img, line, (y),
			get_color(game, y - ceiling_h, wall_h,
				ret_right_tex(game)));
		y++;
	}
	while (y < H)
	{
		my_mlx_pixel_put(&screen->shown_img, line, (y), game->col.f_col);
		y++;
	}
}

void	raycast(t_game *game)
{
	double	d;
	int		ceiling_h;
	int		floor;
	int		w;

	w = 0;
	while (w < W)
	{
		d = get_distance(game, w);
		ceiling_h = H / 2 - H / d;
		floor = H - ceiling_h;
		draw_line(&game->screen, w, ceiling_h, game);
		w++;
	}
}

int	update_window(t_game *game)
{
	t_screen	*screen;
	t_data		*img;

	screen = &game->screen;
	img = &game->screen.shown_img;
	mlx_clear_window(game->screen.ptr, game->screen.win);
	mlx_destroy_image(screen->ptr, screen->shown_img.img);
	img->img = mlx_new_image(game->screen.ptr, W, H);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	update_pos(game);
	raycast(game);
	draw_minimap(game);
	mlx_put_image_to_window(screen->ptr, screen->win, img->img, 0, 0);
	return (0);
}
