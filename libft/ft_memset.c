/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:48:54 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:11:10 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	val;
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)b;
	val = (unsigned char)c;
	while (i < len)
	{
		str[i] = val;
		i++;
	}
	b = str;
	return (b);
}
