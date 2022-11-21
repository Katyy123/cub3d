#include "../inc/cub3d.h"

// t_pt	ft_point(int x, int y)
// {
// 	t_pt	point;

// 	point.x = x;
// 	point.y = y;
// 	return (point);
// }

// float	ft_to_radian(float angle)
// {
// 	float	ret;

// 	ret = angle * M_PI / 180;
// 	return (roundf(ret * 1000000) / 1000000);
// }

// int	ft_trasl(int x, int y, t_game *game)
// {
// 	int		dist;
// 	float	ratio;
// 	t_pt	end;

// 	if (game->pause_game == 0 && game->mouse_block == 1)
// 	{
// 		end = ft_point(x, y);
// 		dist = game->mouse_start.x - end.x;
// 		ratio = ((float)dist * 1.5) / (float)WIN_WIDTH;
// 		ratio *= FOV_D;
// 		game->pos_a += ft_to_radian(ratio);
// 		game->mouse_start = end;
// 		ft_execution(game);
// 	}
// 	return (0);
// }

// int	ft_unlock(int button, int x, int y, t_game *game)
// {
// 	int		dist;
// 	float	ratio;
// 	t_pt	end;

// 	if (game->pause_game == 0 && button == 2)
// 	{
// 		end = ft_point(x, y);
// 		game->mouse_block = 0;
// 		dist = game->mouse_start.x - end.x;
// 		ratio = ((float)dist * 1.5) / (float)WIN_WIDTH;
// 		ratio *= FOV_D;
// 		game->pos_a += ft_to_radian(ratio);
// 		ft_execution(game);
// 	}
// 	return (0);
// }

// int	ft_get_mouse(int button, int x, int y, t_game *game)
// {
// 	if (game->pause_game == 0 && button == 2)
// 	{
// 		game->mouse_block = 1;
// 		game->mouse_start = ft_point(x, y);
// 	}
// 	return (0);
// }