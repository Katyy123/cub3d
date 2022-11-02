/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:19:18 by cfiliber          #+#    #+#             */
/*   Updated: 2022/10/31 19:13:15 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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

char	**read_map_file(char *file_path)
{
	char	**map;
	int		line_count;
	int		fd;
	int		i;

	line_count = file_linecount(file_path);
	if (line_count <= 0)
		return (null_error("the file may not exist"));
	map = malloc(sizeof(char *) * (line_count + 1));
	if (map == NULL)
		return (null_error("malloc failure on read_map()"));
	fd = open(file_path, O_RDONLY);
	i = 0;
	while (i < line_count)
	{
		get_next_line(fd, &map[i]);
		//map[i][ft_strlen(map[i])] = '\0';
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**map_file_parse(char *file_path, t_game *game)
{
	char	**map_file;
	
	map_file = read_map_file(file_path);
	if (!map_file)
		return (NULL);
	//int x;
	//int y ;
	//y = 0;
	//while(map_file[y])
	//{
		//x = 0;
		//while(map_file[y][x])
		//{
			//printf("riga %d, colonna %d: %c\n", y, x, map_file[y][x]);
			//x++;
		//}
		//y++;
	//}
	if (valid_file(map_file, game) == FALSE)
	{
		ft_free_char_mtx(map_file);
		return (NULL);
	}
	return (map_file);
}