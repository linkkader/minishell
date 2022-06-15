/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 20:29:32 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/02 20:31:38 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*p_ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while ((i < len))
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

void	*p_ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (0);
    p_ft_memset(mem, 0, count * size);
	return (mem);
}