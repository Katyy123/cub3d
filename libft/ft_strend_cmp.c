/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strend_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:42:57 by cfiliber          #+#    #+#             */
/*   Updated: 2021/12/10 18:01:29 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns 1 if <name> ends in <extension>, 0 if not */
int	ft_strend_cmp(char *name, char *end)
{
	int	name_len;
	int	ext_len;

	name_len = ft_strlen(name);
	ext_len = ft_strlen(end);
	if (name_len <= ext_len)
		return (0);
	name += name_len - ext_len;
	while (*name)
	{
		if (*name != *end)
			return (0);
		name++;
		end++;
	}
	return (1);
}
