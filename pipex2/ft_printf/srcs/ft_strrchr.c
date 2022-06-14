/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:39:47 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/08 15:33:37 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	character;
	int		a;

	character = (char)c;
	i = 0;
	a = -1;
	while (str[i] != '\0')
	{
		if (str[i] == character)
			a = i;
		i++;
	}
	if (a != -1)
		return ((char *)(str + a));
	if (str[i] == character)
		return ((char *)(str + i));
	return (NULL);
}
