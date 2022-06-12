/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:23:00 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/09 15:50:40 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	character;

	character = (char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == character)
			return ((char *)(str + i));
		i++;
	}
	if (character == '\0')
		return ((char *)(str + i));
	return (NULL);
}
