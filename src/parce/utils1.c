/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:28:29 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/29 15:07:08 by ofarissi         ###   ########.fr       */
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
			return (ft_strdup((g_global.env[i] + j + 1)));
		i++;
	}
	return (NULL);
}

char	*ft_charjoin(char *str, char c)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!str)
		tmp = malloc(2 * sizeof(char));
	else
	{
		tmp = malloc((ft_strlen_parse(str) + 2) * sizeof(char));
		while (str[i])
		{
			tmp[i] = str[i];
			i++;
		}
	}
	tmp[i] = c;
	i++;
	tmp[i] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}

int	ft_strchr_parse(char *s, int c)
{
	if (s)
	{
		while (*s)
		{
			if (*s == c)
				return (1);
			s++;
		}
	}
	return (0);
}

char	*convert_char(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
