/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:44:36 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/27 16:48:07 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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

static int	ft_isalpha_parse(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static int	ft_isdigit_parse(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

char	*get_value(char *value, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	if (value[*i] && value[*i] == '$' && (ft_isalpha_parse(value[(*i) + 1])
			|| value[(*i) + 1] == '_'))
	{
		(*i)++;
		j = *i;
		while (value[*i])
		{
			if (!ft_isalpha_parse(value[*i + 1]) && value[(*i) + 1] != '_'
				&& !ft_isdigit_parse(value[(*i) + 1]))
				break ;
			(*i)++;
		}
		tmp = ft_get_env(ft_substr(value, j, (*i) - j + 1));
	}
	else if (value[*i] == '$' && value[(*i) + 1] == '?')
	{
		tmp = ft_strjoin_parse(tmp, ft_itoa(g_global.exit_code));
		(*i)++;
	}
	return (tmp);
}

char	*ft_expand(char *value)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (value[i])
	{
		if (value[i] == '$')
			str = ft_strjoin_parse(str, get_value(value, &i));
		else
			str = ft_charjoin(str, value[i]);
		i++;
	}
	return (str);
}
