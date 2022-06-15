/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_inside_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:00 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/01 18:53:52 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	replace_inside_quotes(char *str, char new, char old)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			j = i;
			i++;
			while (str[i] && str[i] != str[j])
			{
				if (str[i] == old)
					str[i] = new;
				i++;
			}
		}
	}
}
