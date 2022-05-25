/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/17 20:09:36 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*read_line(int entry)
{
	char	c;
	char	str[1000];
	int		i;

	i = 0;
	while (read(entry, &c, 1))
	{
		str[i++] = c;
		if (c == '\n')
			break ;
	}
	str[i] = '\0';
	return (ft_strdup(str));
}
