/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:45:09 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/23 16:49:10 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_print(va_list ap, char *str, int *count)
{
	int		i;

	i = get(str);
	if (str[i] == 'c')
		case_c(va_arg(ap, int ), count, str);
	else if (str[i] == 's')
		case_s(va_arg(ap, char *), count, str);
	else if (str[i] == 'p')
		case_p(va_arg(ap, void *), count, str);
	else if (str[i] == 'd' || str[i] == 'i')
		case_d(va_arg(ap, int), count, str);
	else if (str[i] == 'u')
		case_u(va_arg(ap, int), count, str);
	else if (str[i] == 'x')
		case_x(va_arg(ap, unsigned int), 0, count, str);
	else if (str[i] == 'X')
		case_x(va_arg(ap, unsigned int), -32, count, str);
	else
		case_c(str[i], count, str);
	return (i);
}

int	ft_printf(const char *string, ...)
{
	va_list		ap;
	int			i;
	char		**list;
	int			count;
	char		*str;

	list = ft_split2(string, '%');
	va_start(ap, string);
	i = start(string, list[0], &count);
	while (list[i] != NULL)
	{
		str = ft_substr(list[i], my_print(ap, list[i], &count) + 1,
				ft_strlen(list[i]));
		ft_putstr(str, &count);
		free(str);
		i++;
	}
	myfree(list);
	free(list);
	return (count);
}
