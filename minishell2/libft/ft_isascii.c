/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:01:48 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/20 14:45:52 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*#include <ctype.h>
int	main()
{
	unsigned char c = (unsigned char)353;
	printf("%d\n", c);
	printf("%d\n", isascii(c));
}*/
