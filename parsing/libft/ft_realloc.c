/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:50:50 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/01 18:52:32 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc(char **ptr, char *new)
{
	int		i;
	int		size;
	char	**new_ptr;

	i = -1;
	size = 0;
	while (ptr[size])
		size++;
	new_ptr = (char **)malloc((size + 2) * sizeof(char *));
	if (!new_ptr)
		return (ptr);
	while (ptr[++i])
	{
		new_ptr[i] = ptr[i];
	}
	free(ptr);
	new_ptr[i++] = new;
	new_ptr[i] = NULL;
	return (new_ptr);
}
