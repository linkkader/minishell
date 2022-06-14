/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:04:34 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 16:16:39 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_ft_strlen(char *str)
{
	if (str != NULL)
		return (ft_strlen(str));
	return (0);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	wr(char c, int *count)
{
	if (c == '.')
		write(1, " ", 1);
	else
		write(1, &c, 1);
	(*count)++;
}

int	ft_str_is_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	another(char *str, int *count, char l, int already)
{
	int		len;

	len = my_ft_strlen(str);
	if (str[0] == '-' && l == '0' && ft_str_is_digit(str + 1))
	{
		wr('-', count);
		if (already > 0)
		{
			while (already-- - len > 0)
				wr(l, count);
			ft_putstr(str + 1, count);
		}
		return (1);
	}
	return (0);
}
