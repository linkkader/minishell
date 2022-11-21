/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:36:51 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 15:20:06 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	check_infile(int *i)
{
	if ((*i) == 0 || (*i) == 1 || (*i) == 4 || (*i) == 2)
	{
		write(2, "syntax error\n", 14);
		return (-1);
	}
	else
		(*i) = 2;
	return (1);
}

int	check_outfile(int *i)
{
	if ((*i) == 0 || (*i) == 1 || (*i) == 2 || (*i) == 4)
	{
		write(2, "syntax error\n", 14);
		return (-1);
	}
	else
		(*i) = 4;
	return (1);
}

int	check_heredoc(int *i)
{
	if ((*i) == 4 || (*i) == 1 || (*i) == 2 || (*i) == 0)
	{
		write(2, "syntax error\n", 14);
		return (-1);
	}
	else
		(*i) = 0;
	return (1);
}

int	check_append(int *i)
{
	if ((*i) == 4 || (*i) == 0 || (*i) == 2 || (*i) == 1)
	{
		write(2, "syntax error\n", 14);
		return (-1);
	}
	else
		(*i) = 1;
	return (1);
}

int	check_pipe(int *i)
{
	if ((*i) == 0 || (*i) == 4 || (*i) == 1 || (*i) == 2 || (*i) == 3)
	{
		write(2, "syntax error\n", 14);
		return (-1);
	}
	else
		(*i) = 3;
	return (1);
}
