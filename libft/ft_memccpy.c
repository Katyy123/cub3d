/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:42:49 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:12:13 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	car;
	size_t			i;

	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dst;
	car = (unsigned char)c;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		if (s1[i] == car)
		{
			s2[i] = s1[i];
			s2 = &s2[i + 1];
			return (s2);
		}
		s2[i] = s1[i];
		i++;
	}
	return (0);
}
