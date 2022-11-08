#include "parsing.h"

/* save the rgb color inside the t_textures struct */
void	save_color(int *col_arr, t_game *game, char *type_id)
{
	//printf("\nIN SAVE_COLOR FUNCTION\n");
    int	col_cod;

	// int i = 0;
	// while (i < 3)
	// {
	// 	printf("col_arr[%d]: %d\n", i, col_arr[i]);
	// 	i++;
	// }
	col_cod = 0 << 24 | col_arr[0] << 16 | col_arr[1] << 8 | col_arr[2];
	//printf("col_cod: %d\n", col_cod);
	if (ft_strncmp(type_id, "F", 1) == 0)
		game->col.f_col = col_cod;
	else if (ft_strncmp(type_id, "C", 1) == 0)
		game->col.c_col = col_cod;
}

/* free type_id, color_mtx and color_arr if they are allocated and return -1 */
int	free_stuff(char *type_id, char **color_mtx, int *color_arr)
{
	free(type_id);
	if (color_mtx)
		ft_free_char_mtx(color_mtx);
	if (color_arr)
		free(color_arr);
	return (-1);
}

/* check every parameter (e.g. red, green or blue) of the color */
int	check_color_param(char *type_id, char **color_mtx, int *color_arr)
{
	int	i;
	
	i = 0;
	while (color_mtx[i])
	{
		if (ft_strlen(color_mtx[i]) > 3)
			return(free_stuff(type_id, color_mtx, color_arr));
		color_arr[i] = ft_atoi(color_mtx[i]);
		if (color_arr[i] == 0 && ft_strncmp(color_mtx[i], "0", ft_strlen(color_mtx[i])) != 0)
			return(free_stuff(type_id, color_mtx, color_arr));
		if (!(color_arr[i] >= 0 && color_arr[i] <= 255))
			return(free_stuff(type_id, color_mtx, color_arr));
		i++;
	}
	return (0);
}

/* check the info about the rgb color */
int	check_color(char *str, t_game *game, t_pos *pos, char *type_id)
{
	//printf("\nIN CHECK_COLOR FUNCTION\n");
    char	**color_mtx;
	int		*color_arr;
	
	color_arr = NULL;
	pos->x += 1;
	while (str[pos->x] == ' ')
		pos->x++;
	color_mtx = ft_split(&str[pos->x], ',');
	if (!color_mtx)
    	return(free_stuff(type_id, color_mtx, color_arr));
	if (ft_char_mtx_linecount(color_mtx) != 3)
		return(free_stuff(type_id, color_mtx, color_arr));
	color_arr = malloc(sizeof(int) * 3);
	if (check_color_param(type_id, color_mtx, color_arr) == -1)
		return (-1);
	save_color(color_arr, game, type_id);
	free_stuff(type_id, color_mtx, color_arr);
	pos->x += ft_strlen(&str[pos->x]) - 1;
	return 0;
}