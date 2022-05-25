/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:00:10 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 16:06:17 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	myfree(char **tab)
{
	int		i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}

int	start(const char *string, char *str, int *count)
{
	*count = 0;
	if (string[0] == '%')
		return (0);
	if (str != NULL)
		ft_putstr(str, count);
	if (str == NULL)
		return (0);
	return (1);
}

int	len_nbr2(unsigned long n)
{
	int		i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa2(unsigned long n)
{
	char	*str;
	int		len;
	int		end;

	if (n == 0)
		return (ft_strdup("0"));
	end = 0;
	len = len_nbr2(n);
	str = malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len >= end)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

int	get(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'd'
			|| str[i] == 'i' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X'
			|| str[i] == '%')
			return (i);
		i++;
	}
	return (0);
}
