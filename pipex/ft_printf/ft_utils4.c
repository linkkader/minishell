/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:18:08 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 18:27:06 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	another2(char *str, int *count, int already)
{
	int		len;
	char	*s;

	if (!ft_str_is_digit(str))
	{
		len = my_ft_strlen(str);
		already = abs(already);
		if (already < len)
		{
			s = ft_substr(str, 0, already);
			ft_putstr(str, count);
			if (s != NULL)
				free(s);
		}
		else
			ft_putstr(str, count);
		return (1);
	}
	return (0);
}

char	sep(char *str)
{
	if (str[0] == '0')
		return ('0');
	if (str[0] == '.')
		return ('.');
	return (' ');
}

void	myptf(char *str, int already, int *count, char l)
{
	int		len;

	len = my_ft_strlen(str);
	while (already - len > 0)
	{
		wr(l, count);
		already--;
	}
	ft_putstr(str, count);
	while (already + len < 0)
	{
		wr(l, count);
		already++;
	}
}

int	str_contains(char *str, char c, int max)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	if (max >= 0)
	{
		while (str[i] != '\0' && i < max)
		{
			if (str[i++] == c)
				return (1);
		}
	}
	else
	{
		while (str[i] != '\0')
		{
			if (str[i++] == c)
				return (1);
		}
	}
	return (0);
}
