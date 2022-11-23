/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:34:47 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/20 17:00:13 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;

	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	if (src < dst)
		while (len-- > 0)
			cdst[len] = csrc[len];
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}

/*#include <stdio.h>
#include <string.h>
int main()
{
   char csrc[100] = "Geeksfor";
   char	*dest = ft_memmove(csrc+5, csrc,strlen(csrc) );
   printf("%s\n", dest);
   return 0;
}*/
