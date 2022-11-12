/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:06 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/18 18:43:27 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	p_ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

void	p_ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
}

int	p_ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*p_ft_strdup(char *s1)
{
	char	*dst;
	size_t	len;

	len = p_ft_strlen(s1) + 1;
	dst = (char *)malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	p_ft_strlcpy(dst, s1, len);
	return (dst);
}

int	p_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - s2[i]));
		i++;
	}
	return (0);
}
