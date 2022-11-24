#include "../inc/cub3d.h"

float	to_radian(float angle)
{
	float	rad;

	rad = angle * M_PI / 180;
	return (roundf(rad * 1000000) / 1000000);
}

int	trasl_mov(int x, int y, t_game *game)
{
	t_coord	end;
	int		dist;
	float	ratio;
	
	if (game->press_mouse == 1)
	{
		end.x = x;
		end.y = y;
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
	t_coord	end;
	int		dist;
	float	ratio;

	if (button == 1)
	{
		end.x = x;
		end.y = y;
		game->press_mouse = 0;
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
		game->press_mouse = 1;
		game->mouse_start.x = x;
		game->mouse_start.y = y;
	}
	return (0);
}