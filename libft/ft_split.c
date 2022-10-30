/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:52:06 by cfiliber          #+#    #+#             */
/*   Updated: 2021/11/16 17:58:54 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	w;
	int	i;
	int	flag;

	w = 0;
	i = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			w++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (w);
}

static char	**ft_allocopy_word(char **arr, char const *s, int j, int len)
{
	int	k;
	int	l;

	arr[0] = malloc(sizeof(char) * (len + 1));
	if (!arr[0])
		return (0);
	k = j - len;
	l = 0;
	while (k < j)
	{
		arr[0][l] = s[k];
		k++;
		l++;
	}
	arr[0][l] = '\0';
	return (arr);
}

static char	**ft_body_ft(char **arr, char const *s, int c, int w)
{
	int	i;
	int	j;
	int	len;
	int	flag;

	i = 0;
	j = 0;
	while (i < w)
	{
		flag = 0;
		len = 0;
		while (s[j] != c && s[j] != '\0')
		{
			flag = 1;
			len++;
			j++;
		}
		if (flag == 1)
			ft_allocopy_word(&arr[i++], s, j, len);
		if (s[j] == c)
			j++;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		w;

	if (!s)
		return (0);
	w = ft_word_count(s, c);
	arr = malloc(sizeof(char *) * (w + 1));
	if (!arr)
		return (0);
	ft_body_ft(arr, s, c, w);
	return (arr);
}
