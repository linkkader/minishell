/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:05:00 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/09 15:57:52 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	myindex(int n, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		n = n / 10;
		i++;
	}
	n = n % 10;
	return ((char)(n + '0'));
}

void	myok(int n, int fd)
{
	if (n == 0)
		ft_putstr_fd("0", fd);
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
}

int	mycheck(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		cp;
	int		len;
	int		i;

	len = 0;
	if (n == 0 || n == -2147483648)
	{
		myok (n, fd);
		return ;
	}
	cp = n;
	n = mycheck(n, fd);
	while (cp != '\0')
	{
		cp /= 10;
		len++;
	}
	i = 0;
	while (i < len)
	{
		ft_putchar_fd(myindex(n, len - i - 1), fd);
		i++;
	}
}
