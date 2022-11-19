/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:32:57 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/19 12:35:55 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

t_token	*next_token(t_lexer *lexer)
{
	t_token	*token;

	token = NULL;
	while (lexer->current != '\0' &&
	lexer->index < ft_strlen(lexer->value))
	{
		if (lexer->current == ' ' || lexer->current == '\t')
			skip_spaces(lexer);
		else if (lexer->current == '<')
		{
			if (lexer->value[lexer->index + 1] == '<')
				return(collect_app_here(lexer, '<', 1));
			else
				return (move_token(lexer, start_token(INFILE, convert_char(lexer))));
			break;
		}
		else if (lexer->current == '>')
		{
			if (lexer->value[lexer->index + 1] == '>')
				return(collect_app_here(lexer, '>', 0));
			else
				return (move_token(lexer, start_token(OUTFILE, convert_char(lexer))));
			break;
		}
		else if (lexer->current == '|')
		{
			return (move_token(lexer, start_token(PIPE, convert_char(lexer))));
			break;
		}
		else if (lexer->current == 0)
		{
			return (move_token(lexer, start_token(T_EOF, convert_char(lexer))));
			break;
		}
	    else
			return (collect_str(lexer));
	}
	return NULL;
}

t_token	*collect_str(t_lexer *lexer)
{
	char	*value;
	char	*str;
	int 	count;
	int 	convert;

	value = NULL;
	count = 0;
	convert = 0;
	// if (lexer->current == '$')
	// 	convert = 1;
	while (is_cmd(lexer->current) && lexer->current != ' ' && lexer->current != '\0')
	{
		if (lexer->current == '\"')
			value = handle_quote(lexer, value, '\"');
		else if (lexer->current == '\'')
			value = handle_quote(lexer, value, '\'');
		else
		{
			str = convert_char(lexer);
			value = ft_strjoin(value, str);
			move_byone(lexer);
		}
	}
	// if (convert == 1)
	// 	value = ft_expand(ft_strdup(value + 1));
	return (start_token(CMD, value));
}

t_token	*collect_app_here(t_lexer *lexer, char c, int i)
{
	char	*value;
	char	*str;
	int q;

	q = 0;
	value = NULL;
	while (lexer->current == c && lexer->current != '\0')
	{
		if (q == 2)
			break;
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
	str[0] = lexer->current;
	str[1] = '\0';
	return (str);
}

char	*handle_quote(t_lexer *lexer, char *value, char q)
{
	char	*str;
	
	str = NULL;
	move_byone(lexer);
	while (lexer->current != q && lexer->current != '\0')
	{
		str = convert_char(lexer);
		value = ft_strjoin(value, str);
		move_byone(lexer);
	}
	if (lexer->current == q)
		move_byone(lexer);
	else if (lexer->current == '\0')
		write(2, "error\n", 6);
	return (value);
}
