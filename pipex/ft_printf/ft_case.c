/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:10:26 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/27 07:02:48 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	case_p(void *v, int *count, char *st)
{
	char	*str;
	int		already;

	already = ft_atoi2(st);
	str = ft_printadress(v, 0);
	case_nbr(str, count, st, already);
	if (str != NULL)
		free(str);
}

void	str_plus(char **a)
{
	char	*str;

	str = a[0];
	a[0] = ft_strjoin("+", a[0]);
	free(str);
}

void	case_d(int a, int *count, char *st)
{
	char	*str;
	int		already;
	char	l;

	already = ft_atoi2(st);
	l = sep(st);
	if (a >= 0 && str_contains(st, ' ', get(st))
		&& !str_contains(st, '+', get(st)))
	{
		wr(' ', count);
		already = decremet(already);
	}
	str = ft_itoa(a);
	if (a >= 0 && str_contains(st, '+', get(st)))
		str_plus(&str);
	if (a < 0 && already < 0 && l == '.')
		already--;
	else if (a < 0 && l == '.')
		already++;
	if (!(l == '.' && already == 0 && a == 0))
		case_nbr(str, count, st, already);
	if (str != NULL)
		free(str);
}

void	case_u(int u, int *count, char *st)
{
	char	*str;
	int		already;

	already = ft_atoi2(st);
	if (u >= 0 && str_contains(st, ' ', get(st)))
		wr(' ', count);
	if (u < 0)
		str = ft_itoa2(4294967296 + u);
	else
		str = ft_itoa(u);
	case_nbr(str, count, st, already);
	if (str != NULL)
		free(str);
}

void	case_x(unsigned long long int adrr, int plus, int *count, char *st)
{
	char	*str;
	int		already;

	already = ft_atoi2(st);
	if (adrr > 0 && str_contains(st, '#', -1))
		str = ft_printadress((void *)adrr, plus);
	else
		str = get_hex(adrr, plus);
	case_nbr(str, count, st, already);
	if (str != NULL)
		free(str);
}
