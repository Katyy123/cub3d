/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:33:53 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/30 17:20:31 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

// t_bool	valid_file(char **map_file)
// {
// 	return TRUE;
// }

// t_file_check_data	map_check_init(char **map)
// {
// 	t_file_check_data	data;

// 	data.size_x = ft_strlen(map[0]);
// 	data.size_y = ft_char_mtx_linecount(map);
// 	data.player = 0;
// 	data.border_walls = TRUE;
// 	data.valid_char = TRUE;
// 	return (data);
// }

// t_bool	valid_map(char **map)
// {
// 	t_file_check_data	data;
// 	t_bool				valid;
// 	int					x;
// 	int					y;

// 	valid = TRUE;
// 	y = 0;
// 	data = map_check_init(map);
// 	while (map[y])
// 	{
// 		is_rectangular(map[y], &data);
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			is_valid_char(map[y][x], &data);
// 			check_border(map[y][x], &data, x, y);
// 			count_chars(&data, map[y][x]);
// 			x++;
// 		}
// 		y++;
// 	}
// 	check_map_size(x, y);
// 	valid = check_map_errors(data);
// 	return (valid);
// }