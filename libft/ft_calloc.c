/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:02:31 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/20 14:15:42 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}

/*#include<stdio.h>
int	main()
{
	int	*arr;
	int	i;

	arr = (int *)ft_calloc(2, sizeof(int));
	i = 0;
	while (i < 2)
	{
		printf("%d\n", arr[i]);
		i++;
	}
}*/
