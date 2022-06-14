/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:55:23 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 15:59:20 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_putchar(char c)
{
	char	*str;

	str = malloc(2 * sizeof (char));
	if (str == NULL)
		return (NULL);
	if (c == 0)
		str[0] = -11;
	else
		str[0] = c;
	str[1] = '\0';
	return (str);
}

void	ft_putstr(char *str, int *count)
{
	int		i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			if (str[i] == -11)
				write(1, "\0", 1);
			else
				write(1, &str[i], 1);
			i++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		i += 6;
	}
	(*count) += i;
}

void	ft_print_hex(unsigned long long int adrr,
		char *str, int *count, int plus)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (adrr >= 16)
	{
		ft_print_hex(adrr / 16, str, count, plus);
		ft_print_hex(adrr % 16, str, count, plus);
	}
	else
	{
		if (adrr < 10)
		{
			str[*count] = hex[adrr];
			(*count)++;
		}
		else
		{
			str[*count] = hex[adrr] + plus;
			(*count)++;
		}
	}
}

char	*get_hex(unsigned long long int adrr, int plus)
{
	char	str[100];
	int		i;

	i = 0;
	while (i < 100)
		str[i++] = '\0';
	i = 0;
	ft_print_hex(adrr, str, &i, plus);
	return (ft_strdup(str));
}

char	*ft_printadress(void *addr, int plus)
{
	char	str[100];
	int		i;

	i = 0;
	while (i < 100)
		str[i++] = '\0';
	str[0] = '0';
	str[1] = 'x' + plus;
	i = 2;
	ft_print_hex((unsigned long long int )addr, str, &i, plus);
	return (ft_strdup(str));
}
