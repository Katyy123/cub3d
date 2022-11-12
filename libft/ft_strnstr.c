/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:57:28 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 18:08:19 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*pagliaio;

	pagliaio = (char *)haystack;
	if (needle[0] == '\0')
		return (pagliaio);
	i = 0;
	while (pagliaio[i] != '\0')
	{
		j = 0;
		while (pagliaio[i + j] == needle[j] && (i + j) < len
			&& pagliaio[i + j] != '\0')
		{
			j++;
			if (needle[j] == '\0')
				return (&pagliaio[i]);
		}
		i++;
	}
	return (0);
}
