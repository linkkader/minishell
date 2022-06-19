/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:05:19 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/17 22:38:46 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_quotes(char *str, char c, int i)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			i = inside_quotes(str, '\"', i);
			if (!str[i])
			{
				write(2, "missing quotes!\n", 17);
				return (0);
			}
		}
		else if (str[i] == '\'')
		{
			i = inside_quotes(str, '\'', i);
			if (!str[i])
			{
				write(2, "missing quotes!\n", 17);
				return (0);
			}
		}
	}
	return (1);
}

int	check_redirect(t_command *commands)
{
	int	i;

	while (commands)
	{
		i = -1;
		while (commands->tokens->tokens[++i])
		{
			if (redirect(commands->tokens->tokens[i]) && ((i && \
			redirect(commands->tokens->tokens[i - 1])) \
			|| !commands->tokens->tokens[i + 1]))
				return (!write(2, "syntax error!\n", 15));
		}
		commands = commands->next;
	}
	return (1);
}
