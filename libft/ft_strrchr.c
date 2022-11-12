/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:58:06 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:07:29 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s2;
	int		i;
	char	car;
	size_t	slen;

	s2 = (char *)s;
	car = (char)c;
	slen = ft_strlen(s);
	i = slen;
	while (i >= 0)
	{
		if (s[i] == car)
			return (s2 + i);
		i--;
	}
	return (0);
}
