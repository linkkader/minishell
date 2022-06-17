/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:29:37 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/04 19:16:19 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = p_ft_strlen(s1);
	len = i + p_ft_strlen(s2) + 1;
	res = (char *)malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	p_ft_strlcpy(res, s1, p_ft_strlen(s1) + 1);
	p_ft_strlcpy(res + i, s2, p_ft_strlen(s2) + 1);
	return (res);
}
