/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:19:43 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 15:20:26 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_check_error(int type, char *content, int *i, t_cmd *data)
{
	int	check;

	check = 1;
	if (type == PIPE && (*i) == -1)
		write(2, "syntax error\n", 14);
	else if (type == INFILE)
		check = check_infile(i);
	else if (type == OUTFILE)
		check = check_outfile(i);
	else if (type == HEREDOC)
		check = check_heredoc(i);
	else if (type == PIPE)
		check = check_pipe(i);
	else if (type == APPEND)
		check = check_append(i);
	else if (type == CMD)
	{
		store_file(data, (*i), content);
		(*i) = 5;
	}
	return (check);
}
