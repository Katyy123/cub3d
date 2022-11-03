#include "map.h"

void	save_color(int *col_arr, t_game *game, char *type_id)
{
	printf("\nIN SAVE_COLOR FUNCTION\n");
    int	col_cod;

	int i = 0;
	while (i < 3)
	{
		printf("col_arr[%d]: %d\n", i, col_arr[i]);
		i++;
	}
	col_cod = 0 << 24 | col_arr[0] << 16 | col_arr[1] << 8 | col_arr[2];
	printf("col_cod: %d\n", col_cod);
	if (ft_strncmp(type_id, "F", 1) == 0)
		game->textures.f_col = col_cod;
	else if (ft_strncmp(type_id, "C", 1) == 0)
		game->textures.c_col = col_cod;
	free(col_arr);
}

int	check_color(char *str, t_game *game, t_pos *pos, char *type_id)
{
	printf("\nIN CHECK_COLOR FUNCTION\n");
    char	**color_mtx;
	int		*color_arr;
	int		i;
	
	pos->x += 1;
	while (str[pos->x] == ' ')
		pos->x++;
	printf("&str[pos->x]: %s\n", &str[pos->x]);
	color_mtx = ft_split(&str[pos->x], ',');
	if (!color_mtx)
    {
        free(type_id);
		return (-1);
    }
	if (ft_char_mtx_linecount(color_mtx) != 3)
	{
		ft_free_char_mtx(color_mtx);
        free(type_id);
		return (-1);
	}
	i = 0;
	color_arr = malloc(sizeof(int) * 3);
	while (color_mtx[i])
	{
		if (ft_strlen(color_mtx[i]) > 3)
		{
			ft_free_char_mtx(color_mtx);
			free(color_arr);
            free(type_id);
			return (-1);
		}
		color_arr[i] = ft_atoi(color_mtx[i]);
		if (color_arr[i] == 0 && ft_strncmp(color_mtx[i], "0", ft_strlen(color_mtx[i])))
		{
			ft_free_char_mtx(color_mtx);
			free(color_arr);
            free(type_id);
			return (-1);
		}
		if (!(color_arr[i] >= 0 && color_arr[i] <= 255))
		{
			ft_free_char_mtx(color_mtx);
			free(color_arr);
            free(type_id);
			return (-1);
		}
		i++;
	}
	ft_free_char_mtx(color_mtx);
	save_color(color_arr, game, type_id);
    free(type_id);
	printf("pos->x: %d\n", pos->x);
	printf("str[pos->x]: %c\n", str[pos->x]);
	//printf("game->textures.f_col = %d\n", game->textures.f_col);
	//printf("game->textures.c_col = %d\n", game->textures.c_col);
	pos->x += ft_strlen(&str[pos->x]) - 1;
	return 0;
}