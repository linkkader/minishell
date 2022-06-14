/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:49:34 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/09 19:10:55 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		a;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		a = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (a != 0)
		{
			return (a);
		}
		i++;
	}
	return (0);
}
