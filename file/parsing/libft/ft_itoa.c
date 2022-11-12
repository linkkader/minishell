/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:45:52 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:45:55 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_nbrlen(int n)
{
	int				i;
	unsigned int	nb;

	i = 0;
	nb = n;
	if (n <= 0)
	{
		nb *= -1;
		i++;
	}
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*p_ft_itoa(int n)
{
	int				i;
	char			*nbr;
	unsigned int	nb;

	nb = n;
	i = get_nbrlen(n);
	if (n < 0)
		nb = -n;
	nbr = (char *)malloc((i + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[0] = '-';
	nbr[i] = 0;
	while (nb > 0)
	{
		nbr[--i] = nb % 10 + 48;
		nb /= 10;
	}
	if (n == 0)
		*nbr = '0';
	return (nbr);
}
