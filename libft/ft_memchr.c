/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:43:21 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:12:01 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	car;
	size_t			i;

	str = (unsigned char *)s;
	car = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == car)
			return (str + i);
		i++;
	}
	return (0);
}
