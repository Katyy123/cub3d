#include "parsing.h"

/* save the path of the texture inside the t_textures struct */
void save_textures(char *str, t_game *game, char *type_id)
{
	printf("\nIN SAVE_TEXTURES FUNCTION\n");
    if (ft_strncmp(type_id, "NO", 2) == 0)
		game->textures.no = str;
	if (ft_strncmp(type_id, "SO", 2) == 0)
		game->textures.so = str;
	if (ft_strncmp(type_id, "WE", 2) == 0)
		game->textures.we = str;
	if (ft_strncmp(type_id, "EA", 2) == 0)
		game->textures.ea = str;
}

/* check the path of the texture */
int	check_texture_path(char *str, t_pos *pos, t_game *game, char *type_id)
{
	printf("\nIN CHECK_TEXTURE_PATH FUNCTION\n");
    int fd;

	pos->x += 2;
	while (str[pos->x] == ' ')
		pos->x++;
	fd = open(&str[pos->x], O_RDONLY);
	if (fd == -1)
	{
		free (type_id);
		return (-1);
	}
	close(fd);
	save_textures(&str[pos->x], game, type_id);
	pos->x += ft_strlen(&str[pos->x]) - 1;//-1 perché poi in valid_file faccio pos.x++
	free (type_id);
	return (0);
}