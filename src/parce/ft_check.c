/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:19:43 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/29 15:07:50 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_check_error(int type, char *content, int *i, t_cmd *data)
{
	int	check;

	check = 1;
	if (type == PIPE && (*i) == -1)
	{
		write(2, "syntax error\n", 14);
		return (-1);
	}
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

void	check_last(int i)
{
	if (i != -1)
		if (i != 5)
			write(2, "syntax error\n", 14);
}

static void	in_quote_checker(char *str, int *i, char c)
{
	(*i)++;
	while (str[(*i)] != c && str[(*i)] != '\0')
	{
		if (ft_isalnum(str[(*i)]) && c == '\'')
			g_global.flag = 1;
		(*i)++;
	}
	if (str[(*i)] == c)
		(*i)++;
}

void	quote_checker(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr_parse(str, '$'))
	{
		while (str[i])
		{
			if (str[i] == '\"')
				in_quote_checker(str, &i, '\"');
			else if (str[i] == '\'')
				in_quote_checker(str, &i, '\'');
			else
				i++;
		}
	}
}

char	*handle_quote(t_lexer *lexer, char *value, char q)
{
	char	*str;

	str = NULL;
	move_byone(lexer);
	while (lexer->c != q && lexer->c != '\0')
	{
		str = convert_char(lexer);
		value = ft_strjoin_parse(value, str);
		move_byone(lexer);
	}
	if (lexer->c == q)
		move_byone(lexer);
	else if (lexer->c == '\0')
	{
		free(value);
		value = NULL;
		write(2, "quote error\n", 13);
		g_global.q_flag = 1;
		return (NULL);
	}
	return (value);
}
