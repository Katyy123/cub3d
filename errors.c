/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:04:12 by cfiliber          #+#    #+#             */
/*   Updated: 2022/11/29 18:02:05 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "parsing/parsing.h"

/* print an error message and return 0 */
int	error(char *message)
{
	printf("\x1b[31m""Error\n%s\n""\x1b[0m", message);
	return (0);
}

/* print an error message and return -1 */
int	error_1(char *message)
{
	printf("\x1b[31m""Error\n%s\n""\x1b[0m", message);
	return (-1);
}

/* print an error message and return NULL */
void	*null_error(char *message)
{
	printf("\x1b[31m""Error\n%s\n""\x1b[0m", message);
	return (NULL);
}

/* print a warning */
void	print_warning(char *message)
{
	printf("\x1b[33m""Warning:\n%s\n""\x1b[0m", message);
}
