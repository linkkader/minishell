/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:59:33 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/09 15:53:33 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;
	size_t	j;

	dlen = 0;
	slen = 0;
	while (dst[dlen] != '\0')
		dlen++;
	while (src[slen] != '\0')
		slen++;
	i = dlen;
	j = 0;
	while (src[j] != '\0' && i < (dstsize - 1) && dstsize != 0)
		dst[i++] = src[j++];
	dst[i] = '\0';
	if (dlen > dstsize)
		return (dstsize + slen);
	return (dlen + slen);
}
