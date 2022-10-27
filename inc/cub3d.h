/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertoli <tbertoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:41:47 by mel-hada          #+#    #+#             */
/*   Updated: 2022/10/26 00:43:59 by tbertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <mlx.h>
//# include "../lib/mlx.h"
# include <math.h>
# include "structs.h"
#include <x86intrin.h>
# include <semaphore.h>

/* utils */
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strlen(const char *str);
int     ft_strlen2(char **str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strchr(const char *str, int c);
char    *get_next_line(int fd);
int	    ft_isdigit(int c);
int	    ft_atoi(const char *str);
void	error(char *str,int m);
int		ft_close(void);
char	*ft_strdup(const char *str);
//t_map	*ft_lst_last(t_map *lst);
//void	ft_lst_del_one(t_map *lst, void (*del)(void*));
//void	ft_lst_clear(t_map **lst, void (*del)(void*));
//void	ft_lst_add_back(t_map **lst, t_map *new);
//void	ft_lst_add_front(t_map **lst, t_map *new);
//t_map	*ft_lst_new(void *content);



#endif