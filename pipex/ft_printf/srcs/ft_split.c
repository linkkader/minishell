/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:22:39 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/13 18:29:56 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ftlen(char const *str, char c)
{
	int		i;
	int		a;

	i = 0;
	a = 1;
	while (str[i] != '\0' && str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			a++;
			while (str[i] == c)
				i++;
			if (str[i] == '\0')
				a--;
		}
		else
			i++;
	}
	return (a);
}

int	lenstr(char const *s, char c, int start)
{
	int		i;

	i = 0;
	while (s[start] != '\0' && s[start] != c)
	{
		start++;
		i++;
	}
	return (i);
}

char	*save(const char *s, char c, int *i, int *len)
{
	char	*str;

	*len = lenstr(s, c, *i);
	str = ft_substr(s, *i, *len);
	*i = *i + *len;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	int		len;
	char	**tab;

	if (s == NULL)
		return (NULL);
	i = 0;
	count = 0;
	len = ftlen (s, c);
	tab = malloc ((len + 1) * sizeof (char *));
	if (tab == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
			tab[count++] = save(s, c, &i, &len);
		else
			i++;
	}
	tab[count] = (NULL);
	return (tab);
}
