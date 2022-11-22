#include "../inc/cub3d.h"

t_coord	point_coord(int x, int y)
{
	t_coord	point;

	point.x = x;
	point.y = y;
	return (point);
}

float	to_radian(float angle)
{
	float	ret;

	ret = angle * M_PI / 180;
	return (roundf(ret * 1000000) / 1000000);
}

int	trasl_mov(int x, int y, t_game *game)
{
	int		dist;
	float	ratio;
	t_coord	end;

	if (game->mouse_block == 1)
	{
		end = point_coord(x, y);
		dist = game->mouse_start.x - end.x;
		ratio = ((float)dist * 1.5) / (float)W;
		ratio *= MOUSE_SPEED;
		game->pl.pov += to_radian(ratio);
		game->mouse_start = end;
		update_window(game);
	}
	return (0);
}

int	unlock_mouse(int button, int x, int y, t_game *game)
{
	int		dist;
	float	ratio;
	t_coord	end;

	if (button == 1)
	{
		end = point_coord(x, y);
		game->mouse_block = 0;
		dist = game->mouse_start.x - end.x;
		ratio = ((float)dist * 1.5) / (float)W;
		ratio *= MOUSE_SPEED;
		game->pl.pov += to_radian(ratio);
		update_window(game);
	}
	return (0);
}

int	get_mouse(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		game->mouse_block = 1;
		game->mouse_start = point_coord(x, y);
	}
	return (0);
}