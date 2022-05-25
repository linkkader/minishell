/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:21:33 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/13 17:22:52 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	len_str;

	if (s == NULL)
		return (NULL);
	len_str = ft_strlen(s);
	i = 0;
	while (s[start + i])
		i++;
	if (len > i)
		len = i;
	i = 0;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < (len) && start < len_str)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
