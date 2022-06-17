/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:44:51 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/08 14:32:24 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	character;

	character = (unsigned)c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*str == character)
			return ((void *)(str));
		str++;
		i++;
	}
	return (NULL);
}
