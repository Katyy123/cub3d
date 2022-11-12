/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:58:49 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 18:09:59 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_beg(char const *s1, char const *set)
{
	int		beg;
	int		j;
	int		flag;

	beg = 0;
	flag = 0;
	while (s1[beg] != '\0' && flag == 0)
	{
		j = 0;
		while (set[j] != '\0' && s1[beg] != set[j])
			j++;
		if (s1[beg] == set[j])
			beg++;
		if (set[j] == '\0')
			flag = 1;
	}
	return (beg);
}

static int	ft_check_end(char const *s1, char const *set)
{
	int		end;
	int		j;
	int		flag;

	end = ft_strlen(s1) - 1;
	flag = 0;
	while (end >= 0 && flag == 0)
	{
		j = 0;
		while (set[j] != '\0' && s1[end] != set[j])
			j++;
		if (s1[end] == set[j])
			end--;
		if (set[j] == '\0')
			flag = 1;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		beg;
	int		end;
	int		i;

	if (!s1 || !set)
		return (0);
	beg = ft_check_beg(s1, set);
	end = ft_check_end(s1, set);
	if ((end - beg) <= 0)
		beg = end + 1;
	str = malloc(sizeof(char const) * (end - beg + 2));
	if (!str)
		return (0);
	i = 0;
	while (beg <= end)
		str[i++] = s1[beg++];
	str[i] = '\0';
	return (str);
}
