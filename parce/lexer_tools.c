/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:49:52 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/25 16:04:07 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

t_lexer	*start_lexer(char *value)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->value = value;
	lexer->index = 0;
	lexer->c = value[lexer->index];
	return (lexer);
}

t_token	*start_token(int type, char *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->content = content;
	return (token);
}

void	move_byone(t_lexer *lexer)
{
	if (lexer->c != '\0')
	{
		if (lexer->index < ft_strlen_parse(lexer->value))
		{
			lexer->index += 1;
			lexer->c = lexer->value[lexer->index];
		}
	}
}

void	skip_spaces(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t')
		move_byone(lexer);
}

t_token	*move_token(t_lexer *lexer, t_token *token)
{
	move_byone(lexer);
	return (token);
}
