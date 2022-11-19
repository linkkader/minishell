/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:36:51 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/19 13:08:45 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"


int	ft_check_error(int type, char *content, int *i, t_cmd *data)
{
	int check;

	check = 1;
	if (type == PIPE && (*i) == -1)
		write(2, "syntax error\n", 14);
	else if (type == INFILE)
		check = check_infile(content, i);
	else if (type == OUTFILE)
		check = check_outfile(content, i);
	else if (type == HEREDOC)
		check = check_heredoc(content, i);
	else if (type == PIPE)
		check = check_pipe(content, i);
	else if (type == APPEND)
		check = check_append(content, i);
	else if (type == CMD)
	{
		store_file(data, (*i), content);
		(*i) = 5;
	}
	return check;
}

int	check_infile(char *content, int *i)
{
	(void)content;
	if ((*i) == 0 || (*i) == 1 || (*i) == 4 || (*i) == 2)
	{
		write(2, "syntax error\n", 14);
		return -1;
	}
	else
		(*i) = 2;
	return 1;
}

int	check_outfile(char *content, int *i)
{
	(void)content;
	if ((*i) == 0 || (*i) == 1|| (*i) == 2 || (*i) == 4)
	{
		write(2, "syntax error\n", 14);
		return -1;
	}
	else
		(*i) = 4;
	return 1;
}

int	check_heredoc(char *content, int *i)
{
	(void)content;
	if ((*i) == 4 || (*i) == 1|| (*i) == 2 || (*i) == 0)
	{
		write(2, "syntax error\n", 14);
		return -1;
	}
	else
		(*i) = 0;
	return 1;
}

int	check_append(char *content, int *i)
{
	(void)content;
	if ((*i) == 4 || (*i) == 0 || (*i) == 2 || (*i) == 1)
	{
		write(2, "syntax error\n", 14);
		return -1;
	}
	else
		(*i) = 1;
	return 1;
}

int	check_pipe(char *content, int *i)
{
	(void)content;
	if ((*i) == 0 || (*i) == 4 || (*i) == 1|| (*i) == 2 || (*i) == 3)
	{
		write(2, "syntax error\n", 14);
		return -1;
	}
	else
		(*i) = 3;
	return 1;
}
