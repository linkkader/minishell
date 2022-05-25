/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:22:39 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/13 18:29:56 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *quote(char *str, char *name)
{
	char *line;
	char *temp;

	line = readline(name);
	temp = str;
	str = ft_strjoin(str, line);
	free(temp);
	free(line);
	temp = str;
	str = ft_strjoin(str, "\n");
	free(temp);
	return (str);
}

static char *ftlen(char *str, char c, int *a)
{
	int		i;

	i = 0;
	*a = 1;
	while (str[i] != '\0' && str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '"' )
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '"')
				(*a)++;
			else
				return (ftlen(quote(str, "dquote> "), ' ', a));
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				(*a)++;
			else
				return (ftlen(quote(str, "quote> "), ' ', a));
		}
		if (str[i] == c)
		{
			(*a)++;
			while (str[i] == c)
				i++;
			if (str[i] == '\0')
				(*a)--;
		}
		else
			i++;
	}
	return (str);
}

static int	lenstr(char const *s, char c, int start)
{
	int		i;

	i = 0;
	while (s[start] != '\0' && s[start] != c)
	{
		start++;
		i++;
	}
	return (i);
}

static char	*save(const char *s, char c, int *i, int *len)
{
	char	*str;

	*len = lenstr(s, c, *i);
	str = ft_substr(s, *i, *len);
	*i = *i + *len;
	return (str);
}

char	**split_string(char *s, char c)
{
	int		i;
	int		count;
	int		len;
	char	**tab;

	if (s == NULL)
		return (NULL);
	i = 0;
	count = 0;
	s = ftlen (s, c, &len);
	printf("%d\n",len);
	tab = malloc ((len + 1) * sizeof (char *));
	if (tab == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
			tab[count++] = save(s, c, &i, &len);
		else
			i++;
	}
	tab[count] = (NULL);
	return (tab);
}
