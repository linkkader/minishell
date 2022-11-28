/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:28:29 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/28 12:06:19 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	*ft_strdup_parse(char *s1)
{
	int		x;
	int		len;
	char	*dup;

	x = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen_parse(s1);
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

char	*ft_get_env(char *name)
{
	int		i;
	int		j;

	i = 0;
	while (g_global.env[i])
	{
		j = 0;
		while (name[j] && g_global.env[i][j])
		{
			if (name[j] != g_global.env[i][j])
				break ;
			j++;
		}
		if (name[j] == '\0' && g_global.env[i][j] == '=')
			return ft_strdup((g_global.env[i] + j + 1));
		i++;
	}
	return (NULL);
}