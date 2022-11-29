/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:33:19 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/27 11:07:48 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	*ft_substr_parse(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	str_l;
	size_t			cnv;
	char			*rslt;

	cnv = len + 1;
	if (cnv >= (size_t)ft_strlen_parse(s))
		cnv = ft_strlen_parse(s);
	rslt = malloc(cnv * sizeof(char));
	if (!s || !rslt)
		return (0);
	i = 0;
	str_l = ft_strlen_parse(s);
	while (s[start + i] && i < len && start < str_l)
	{
		rslt[i] = s[start + i];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}

int	ft_strlen_parse(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_parse(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
		j = ft_strlen_parse(s1);
	if (s2)
		j += ft_strlen_parse(s2);
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
		return (1);
	return (0);
}
