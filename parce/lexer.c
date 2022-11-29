/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:32:57 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/29 15:07:34 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

static t_token	*is_here(t_lexer *lexer)
{
	if (lexer->value[lexer->index + 1] == '>')
		return (collect_app_here(lexer, '>', 1));
	else
		return (move_token(lexer,
				start_token(INFILE, convert_char(lexer))));
	return (NULL);
}

static t_token	*is_app(t_lexer *lexer)
{
	if (lexer->value[lexer->index + 1] == '<')
		return (collect_app_here(lexer, '<', 0));
	else
		return (move_token(lexer,
				start_token(OUTFILE, convert_char(lexer))));
	return (NULL);
}

t_token	*next_token(t_lexer *lexer)
{
	while (lexer->c != '\0'
		&& lexer->index < ft_strlen_parse(lexer->value))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_spaces(lexer);
		else if (lexer->c == '<')
		{
			return (is_here(lexer));
			break ;
		}
		else if (lexer->c == '>')
		{
			return (is_app(lexer));
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
	while (is_cmd(lexer->c) && lexer->c != ' '
		&& lexer->c != '\t' && lexer->c != '\0')
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
			value = ft_strjoin_parse(value, str);
			move_byone(lexer);
		}
	}
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
		value = ft_strjoin_parse(value, str);
		q += 1;
		move_byone(lexer);
	}
	if (i == 1)
		return (start_token(HEREDOC, value));
	return (start_token(APPEND, value));
}
