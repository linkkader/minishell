/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:28:29 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 15:29:04 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_strchr(char *s, int c)
{
	if (s)
	{
		while (*s != (unsigned char)c)
		{
			if (*s == '\0')
				return (0);
			s++;
		}
	}
	return (1);
}

char	*ft_strdup(char *s1)
{
	int		x;
	int		len;
	char	*dup;

	x = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc((len + 1) * sizeof(*dup));
	if (!dup)
		return (NULL);
	while (x < len)
	{
		dup[x] = s1[x];
		x++;
	}
	dup[len] = '\0';
	return (dup);
}
