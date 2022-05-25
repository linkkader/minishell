/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:14:26 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/27 07:03:29 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	check1(char l)
{
	if (l == '.')
		l = '0';
	return (l);
}

void	case_nbr(char *string, int *count, char *st, int already)
{
	char	*str;
	int		len;
	int		abs;
	char	l;

	l = check1(sep(st));
	if (string == NULL)
		str = (NULL);
	else
		str = ft_strdup(string);
	len = my_ft_strlen(str);
	abs = ft_abs(already);
	if (abs > len)
	{
		if (l == '0' && another(str, count, l, already))
			l = '0';
		else
			myptf(str, already, count, l);
	}
	else
		ft_putstr(str, count);
	if (str != NULL)
		free(str);
}

void	case_str_chiant(char *str, int already, int *count)
{
	int		len;
	char	*s;

	len = my_ft_strlen(str);
	if (already < len)
	{
		s = ft_substr(str, 0, already);
		ft_putstr(s, count);
		if (s != NULL)
			free(s);
	}
	else
		ft_putstr(str, count);
}

void	case_s(char *string, int *count, char *st)
{
	char	*str;
	int		already;
	char	l;

	already = ft_atoi2(st);
	l = sep(st);
	if (string == NULL)
		str = (NULL);
	else
		str = ft_strdup(string);
	if (l == '.')
		case_str_chiant(str, already, count);
	else
		case_nbr(str, count, st, already);
	if (str != NULL)
		free(str);
}

void	case_c(char c, int *count, char *st)
{
	char	*str;
	int		len;
	int		abs;
	int		already;
	char	l;

	already = ft_atoi2(st);
	l = sep(st);
	str = ft_putchar(c);
	len = my_ft_strlen(str);
	abs = ft_abs(already);
	if (abs > len)
	{
		if (l == '0' && another(str, count, l, already))
			return ;
		if (l == '.' && another2(str, count, already))
			return ;
		myptf(str, already, count, l);
	}
	else
		ft_putstr(str, count);
	if (str != NULL)
		free(str);
}
