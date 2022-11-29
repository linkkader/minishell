/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:44:41 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/20 16:12:34 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include<stdlib.h>

static int	sp(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	ft_count_word(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && !sp(str[i], c))
			count++;
		else if (!sp(str[i], c) && sp(str[i - 1], c))
			count++;
		i++;
	}
	return (count);
}

static int	*ft_size_word(const char *str, char c)
{
	int	i;
	int	j;
	int	*size;
	int	count;

	count = ft_count_word(str, c) - 1;
	i = 0;
	j = -1;
	size = (int *)malloc(count * sizeof(int));
	if (!size)
		return (NULL);
	while (++j < count)
		size[j] = 1;
	j = 0;
	while (sp(str[i], c))
		i++;
	while (str[i])
	{
		if (!sp(str[i], c))
			size[j]++;
		else if (sp(str[i], c) && !sp(str[i + 1], c))
			j++;
		i++;
	}
	return (size);
}

static char	**ft_free(char **words, int *size, int j)
{
	while (--j >= 0)
	{
		free(words[j]);
		j--;
	}
	free(words);
	free(size);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		*size;
	int		j;
	int		i;

	j = 0;
	i = -1;
	size = ft_size_word(s, c);
	words = (char **)ft_calloc(ft_count_word(s, c), sizeof(char *));
	if (!words || !s)
		return (NULL);
	while (s[++i])
	{
		if ((i == 0 && !sp(s[i], c)) || (!sp(s[i], c) && sp(s[i - 1], c)))
		{
			words[j] = (char *)ft_calloc(size[j], sizeof(char));
			if (!words[j])
				return (ft_free(words, size, j));
			ft_strlcpy(words[j], ((char *)s + i), size[j]);
			j++;
		}
	}
	free(size);
	return (words);
}
