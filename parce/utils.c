/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:33:19 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/19 13:22:52 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
		j = ft_strlen(s1);
	if (s2)
		j += ft_strlen(s2);
	str = malloc((j + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	if (s1)
		while (s1[i])
			str[i++] = s1[j++];
	j = 0;
	if (s2)
		while (s2[j])
			str[i++] = s2[j++];
	free(s1);
	free(s2);
	str[i] = '\0';
	return (str);
}

int	is_cmd(char c)
{
	if (c != '<' && c != '>' && c != '|')
		return 1;
	return 0;
}

char	*ft_strdup(char *s1)
{
	int		x;
	int		len;
	char	*dup;

	x = 0;
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
