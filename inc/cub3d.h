/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:39:28 by tbertoli          #+#    #+#             */
/*   Updated: 2022/11/26 17:29:20 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
# define CUB3D_H

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17

# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_I			34
# define KEY_O			31
# define KEY_P			35
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125

# define KEY_TAB	48
# define KEY_MAJ	257
# define KEY_ESC	53
# define KEY_TAB	48


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
//# include <fcntl.h>
//# include <pthread.h>
# include <mlx.h>
//# include "../lib/mlx.h"
# include <math.h>
# include <time.h>
# include "structs.h"
//#include <x86intrin.h>
//# include <semaphore.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

/* minimap */
# define MAP_WALL_COL           0x00505050
# define MAP_BACK_COL           0x00F0F0E0 
# define MAP_BORDER_COL         0x00000000
# define MAP_EMPTY_COL          0x00FFFFFF
# define MAP_PLAYER_COL         0x00FF0000

/* minimap.c */
void    init_minimap(t_game *game);
void    draw_wall(t_game *game, int tile_x, int tile_y);
void    draw_player(t_game *game);
void    draw_minimap(t_game * game);

/* minimap_background.c */
void    draw_border(t_game *game);
void    draw_background(t_game *game);

/* minimap_utils.c */
t_bool  is_pix_in_minimap(t_game *game, int x, int y);
t_bool  is_tile_in_minimap(t_game *game, int x, int y);
t_bool	is_inside_circle(t_game *game, int x, int y);



int wall_f1(t_game *game);
int wall_f2(t_game *game);
int wall_b1(t_game *game);
int wall_b2(t_game *game);
int wall_dx(t_game *game);
int wall_sx(t_game *game);

/* errors.c */
int		error(char *message);
int     error_1(char *message);
void	*null_error(char *message);
void	print_warning(char *message);

/* cub3d.c */ // ne mancano un po!
double	to_degrees(double rad);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int     ft_strlen(const char *str);
char	*ft_strdup(const char *str);
void    ft_init1(t_game *game);
void    ft_init_tex(t_game *game);
void    ft_init2(t_game *game);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 	pixel_col_put(t_screen *screen, int x, int y, int color, int pxnum);
double 	get_distance(t_game *game, int w);
t_tex 	*select_text(t_game *game);
int     get_color(t_game *game, int y, int wall_h, t_tex tex);
void 	draw_line(t_screen *screen, int line, double ceiling_h, t_game *game);
int		update_window(t_game *game);
int 	check_pos(t_game *game);
int 	key_press(int keycode, t_game *game);
int     key_rlease(int keycode, t_game *game);

/* end_program.c */
int		end_program(t_game *game);

# endif