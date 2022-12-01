/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*													  +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:49:43 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/14 09:49:34 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "minishell.h"

t_cmd	*is_error_1(t_cmd *to_free, int i, t_token *tmp)
{
	g_global.exit_code = 258;
	if (tmp)
	{
		free(tmp->content);
		free(tmp);
	}
	free_list(to_free);
	check_last(i);
	return (NULL);
}

void	ft_pipe_(t_cmd **data, int i)
{
	if (i == 3)
	{
		(*data)->next = malloc(sizeof(t_cmd));
		(*data) = (*data)->next;
		(*data)->file = NULL;
		(*data)->cmd = NULL;
		(*data)->next = NULL;
	}
}

t_cmd	*ft_parce(t_lexer *lexer, t_token *token, t_cmd **data)
{
	t_cmd	*tmp;
	t_token	*tmp_tok;
	int		i;

	i = -1;
	(*data) = malloc(sizeof(t_cmd));
	(*data)->file = NULL;
	(*data)->cmd = NULL;
	(*data)->next = NULL;
	tmp = (*data);
	while (token != NULL)
	{
		if (token->content && (ft_check_error(token->e_type, token->content,
					&i, (*data)) == -1
				|| token->content[0] == '\0'))
			return (is_error_1(tmp, i, token));
		ft_pipe_(data, i);
		tmp_tok = token;
		token = next_token(lexer);
		free(tmp_tok->content);
		free(tmp_tok);
	}
	if (i != 5 || g_global.q_flag)
		return (is_error(tmp, i));
	return (tmp);
}

static int	how_many(char *s, int c)
{
	int	i;

	i = 0;
	if (s[i])
	{
		while (s[i])
		{
			if (s[i] == c)
				return (i);
			i++;
		}
	}
	return (0);
}

void	parse(void)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = NULL;
	token = NULL;
	g_global.q_flag = 0;
	g_global.flag = 0;
	quote_checker(g_global.line);
	if (ft_strchr_parse(g_global.line, '$') == 1)
		if (g_global.flag != 1 && g_global.line[how_many(g_global.line,
					'$') + 1] != '$' && g_global.line[how_many(
					g_global.line, '$') + 1] != '\0')
			g_global.line = ft_expand(g_global.line);
	if (g_global.line != NULL)
	{
		lexer = start_lexer(g_global.line);
		token = next_token(lexer);
		g_global.cmds = ft_parce(lexer, token, &g_global.cmds);
		free(lexer);
	}
}
