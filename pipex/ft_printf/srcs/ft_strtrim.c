/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:49:12 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/13 17:27:29 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_chr_in(int c, char const *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	left(char const *str, char const *set)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!is_chr_in(str[i], set))
			return (i);
		i++;
	}
	return (i);
}

int	right(char const *str, char const *set)
{
	int		i;
	int		a;

	i = ft_strlen(str) - 1;
	a = 0;
	while (i >= 0)
	{
		if (is_chr_in(str[i], set))
			a++;
		else
			break ;
		i--;
	}
	return (a);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		a;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = left(s1, set);
	len = ft_strlen(s1) - start - right(s1, set);
	if (len < 0)
		len = 0;
	str = malloc ((len + 1) * sizeof (char));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (a < len)
		str[a++] = s1[start++];
	str[a] = '\0';
	return (str);
}
