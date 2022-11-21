/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:32:57 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 15:54:56 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

t_token	*next_token(t_lexer *lexer)
{
	t_token	*token;

	token = NULL;
	while (lexer->c != '\0'
		&& lexer->index < ft_strlen(lexer->value))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_spaces(lexer);
		else if (lexer->c == '<')
		{
			if (lexer->value[lexer->index + 1] == '<')
				return (collect_app_here(lexer, '<', 1));
			else
				return (move_token(lexer,
						start_token(INFILE, convert_char(lexer))));
			break ;
		}
		else if (lexer->c == '>')
		{
			if (lexer->value[lexer->index + 1] == '>')
				return (collect_app_here(lexer, '>', 0));
			else
				return (move_token(lexer,
						start_token(OUTFILE, convert_char(lexer))));
			break ;
		}
		else if (lexer->c == '|')
		{
			return (move_token(lexer, start_token(PIPE, convert_char(lexer))));
			break ;
		}
		else
			return (collect_str(lexer));
	}
	return (NULL);
}

t_token	*collect_str(t_lexer *lexer)
{
	char	*value;
	char	*str;
	int		flag;

	value = NULL;
	flag = 0;
	while (is_cmd(lexer->c) && lexer->c != ' ' && lexer->c != '\0')
	{
		if (lexer->c == '\"')
			value = handle_quote(lexer, value, '\"');
		else if (lexer->c == '\'')
		{
			value = handle_quote(lexer, value, '\'');
			flag = 1;
		}
		else
		{
			str = convert_char(lexer);
			value = ft_strjoin(value, str);
			move_byone(lexer);
		}
	}
	if (ft_strchr(value, '$') == 1 && flag == 0)
		value = ft_expand(value);
	return (start_token(CMD, value));
}

t_token	*collect_app_here(t_lexer *lexer, char c, int i)
{
	char	*value;
	char	*str;
	int		q;

	q = 0;
	value = NULL;
	while (lexer->c == c && lexer->c != '\0')
	{
		if (q == 2)
			break ;
		str = convert_char(lexer);
		value = ft_strjoin(value, str);
		q += 1;
		move_byone(lexer);
	}
	if (i == 1)
		return (start_token(HEREDOC, value));
	return (start_token(APPEND, value));
}

char	*convert_char(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*handle_quote(t_lexer *lexer, char *value, char q)
{
	char	*str;

	str = NULL;
	move_byone(lexer);
	while (lexer->c != q && lexer->c != '\0')
	{
		str = convert_char(lexer);
		value = ft_strjoin(value, str);
		move_byone(lexer);
	}
	if (lexer->c == q)
		move_byone(lexer);
	else if (lexer->c == '\0')
	{
		write(2, "quote error\n", 13);
		return (ft_strdup(""));
	}
	return (value);
}
