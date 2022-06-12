/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:22:39 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 16:34:28 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftlen2(char const *str, char c)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (str[i] != c)
		a = 1;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			if (str[++i] == '\0')
				break ;
			a++;
		}
		i++;
	}
	return (a);
}

int	lenstr2(char const *s, char c, int start)
{
	int		i;

	i = 0;
	if (s[start] == c)
	{
		i++;
		start++;
	}
	while (s[start] != '\0' && s[start] != c)
	{
		start++;
		i++;
	}
	return (i);
}

char	*save2(const char *s, char c, int *i)
{
	char	*str;
	int		len;

	len = lenstr2(s, c, *i);
	str = ft_substr(s, *i, len);
	*i = *i + len;
	return (str);
}

char	*first(const char *str, int *i, int *count, char c)
{
	*i = 0;
	if (str[*i] == c)
	{
		*count = 0;
		return (NULL);
	}
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	return (ft_substr(str, 0, *i));
}

char	**ft_split2(char const *s, char c)
{
	int		i;
	int		count;
	int		len;
	char	**tab;

	if (s == NULL)
		return (NULL);
	count = 1;
	len = ftlen2 (s, c);
	tab = malloc ((len + 1) * sizeof (char *));
	if (tab == NULL)
		return (NULL);
	tab[0] = first(s, &i, &count, c);
	while (s[i] != '\0' && count < len)
	{
		if (s[i++] == c)
			tab[count++] = save2(s, c, &i);
	}
	if (tab[count - 1] != NULL)
		tab[count] = (NULL);
	return (tab);
}
/*
int main()
{
    char **str;

    str = ft_split2("%ddd%d%s%i%%% ", '%');
    int i = 0;
    while (str[i] != NULL)
    {
        printf("%s\n", str[i]);
        i++;
    }
    return (0);
}*/
