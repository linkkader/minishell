/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:37:12 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/13 17:24:31 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		a;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	a = 0;
	while (s1[i] != '\0')
		str[a++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		str[a++] = s2[i++];
	str[a] = '\0';
	return (str);
}
