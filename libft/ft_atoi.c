/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:17:10 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/11 17:14:17 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	mysign(const char *str, int *i)
{
	int		sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	unsigned long	n;
	int				i;
	int				sign;

	n = 0;
	i = check(str);
	sign = mysign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			n = (n + str[i] - '0') * 10;
		else
			n = n + str[i] - '0';
		i++;
		if (n > 2147483647 && sign == 1)
			return (-1);
		if (n > 2147483648 && sign == -1)
			return (0);
	}
	return (n * sign);
}
