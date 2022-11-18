/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:19:18 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/17 20:24:46 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* check if the argument is valid */
int	valid_arg(int argc, char *file_path)
{
	if (argc == 1)
		return (error("there is no map file"));
	if (argc > 2)
		print_warning("only the first file will be used");
	if (!ft_strend_cmp(file_path, ".cub"))
		return (error("map should be a .cub file"));
	return (1);
}

/* count the lines of the file */
int	file_linecount(char *file)
{
	int		linecount;
	int		fd;
	int		readcount;
	char	c;	

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 0;
	while (TRUE)
	{
		readcount = read(fd, &c, 1);
		if (readcount == 0)
			break ;
		if (readcount < 0)
			return (-1);
		if (c == '\n')
			linecount++;
	}
	if (linecount != 0)
		linecount++;
	close(fd);
	return (linecount);
}

/* read the file and return a matrix that is a copy of the file */
char	**read_map_file(char *file_path)
{
	char	**map_file;
	int		line_count;
	int		fd;
	int		i;

	line_count = file_linecount(file_path);
	if (line_count < 0)
		return (null_error("the file may not exist"));
	map_file = malloc(sizeof(char *) * (line_count + 1));
	if (map_file == NULL)
		return (null_error("malloc failure on read_map()"));
	fd = open(file_path, O_RDONLY);
	i = 0;
	while (i < line_count)
	{
		get_next_line(fd, &map_file[i]);
		i++;
	}
	map_file[i] = NULL;
	close(fd);
	return (map_file);
}

/* free the textures paths */
void	free_textures(t_game *game)
{
	if (game->no_tex.path)
		free(game->no_tex.path);
	if (game->so_tex.path)
		free(game->so_tex.path);
	if (game->we_tex.path)
		free(game->we_tex.path);
	if (game->ea_tex.path)
		free(game->ea_tex.path);
}

/* parsing of the file */
int	map_file_parse(char *file_path, t_game *game)
{
	char	**map_file;

	map_file = read_map_file(file_path);
	if (!map_file)
		return (-1);
	if (valid_file(map_file, game) == FALSE)
	{
		free_textures(game);
		ft_free_char_mtx(map_file);
		return (-1);
	}
	ft_free_char_mtx(map_file);
	return (0);
}
