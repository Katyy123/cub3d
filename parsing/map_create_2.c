/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:41:13 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/12 19:17:36 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* allocate every map string */
int	alloc_map_strings(t_game *game, int max_len, int *len_str, int i)
{
	game->map[i] = malloc(sizeof(char) * max_len + 1);
	if (!game->map[i])
	{
		free (len_str);
		error("can't do malloc game->map[i] in valid_map");
		return (-1);
	}
	return (0);
}

/* find the maximum length of the map rows */
int	find_max_strlen(char **map_file, int *len_str, int lines_to_remove)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = 0;
	while (map_file[i + lines_to_remove])
	{
		len_str[i] = ft_strlen(map_file[i]);
		if (len_str[i] > max_len)
			max_len = len_str[i];
		i++;
	}
	return (max_len);
}

/* allocate memory for len_str and map */
int	*alloc_lenstr_map(char **map_file, t_game *game, int lines_to_remove)
{
	int	lines_n;
	int	*len_str;

	lines_n = ft_char_mtx_linecount(map_file) - lines_to_remove;
	len_str = malloc(sizeof(int) * (lines_n + 1));
	if (!len_str)
		return (null_error("can't do malloc len_str in valid_map"));
	game->map = malloc(sizeof(char *) * (lines_n + 1));
	if (!game->map)
	{
		free (len_str);
		return (null_error("can't do malloc game->map in valid_map"));
	}
	return (len_str);
}

/* create the map adding spaces at the end of the lines
to have them the same length */
int	create_map(char **map_file, t_game *game, int lines_to_remove)
{
	int	i;
	int	max_len;
	int	*len_str;

	len_str = alloc_lenstr_map(map_file, game, lines_to_remove);
	if (!len_str)
		return (FALSE);
	max_len = find_max_strlen(map_file, len_str, lines_to_remove);
	i = 0;
	while (map_file[i + lines_to_remove])
	{
		if (alloc_map_strings(game, max_len, len_str, i) == -1)
			return (-1);
		ft_memcpy((void *)game->map[i], (void *)map_file[i], len_str[i]);
		if (len_str[i] < max_len)
			ft_memset((void *)&game->map[i][len_str[i]],
				' ', max_len - len_str[i]);
		game->map[i][max_len] = '\0';
		i++;
	}
	game->map[i] = NULL;
	game->map_x = max_len;
	game->map_y = ft_char_mtx_linecount(game->map);
	free (len_str);
	return (0);
}
