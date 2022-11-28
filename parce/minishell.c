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

void	in_quote_checker(char *str, int *i, char c)
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
	int i;

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

void	free_table(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_data(t_cmd *data)
{
	t_file	*tmp;
	t_cmd	*tmp1;

	free(g_global.line);
	g_global.line = NULL;
	while (data)
	{
		while (data->file)
		{
			tmp = data->file;
			data->file = data->file->next;
			free(tmp->name);
			free(tmp);
		}
		if (data->cmd)
			free_table(data->cmd);
		tmp1 = data;
		data = data->next;
		free(tmp1);
		tmp1 = NULL;
	}
}


void	check_last(int i)
{
	if (i != -1)
		if (i != 5)
			write(2, "syntax error\n", 14);
}


void	print_cmd(t_cmd *data)
{
	int i = 0;
	while(data)
	{
		while (data->file)
		{
			printf("token( %d) name (%s)\n", data->file->token, data->file->name);
			data->file = data->file->next;
		}
		i = 0;
		while(data->cmd && data->cmd[i])
		{
			printf("cmd :: %s\n", data->cmd[i]);
			i++;
		}
		printf("================\n");
		data = data->next;
	}
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
	t_cmd *tmp;
	t_token *tmp_tok;
	int 	i;

	i = -1;
	(*data) = malloc(sizeof(t_cmd));
	(*data)->file = NULL;
	(*data)->cmd = NULL;
	(*data)->next = NULL;
	tmp = (*data);
	while (token != NULL)
	{
		if (token->content && (ft_check_error(token->type, token->content, &i, (*data)) == -1
			|| token->content[0] == '\0'))
		{
			free_data(tmp);
			check_last(i);
			return NULL;
		}
		ft_pipe_(data, i);
		tmp_tok = token;
		token = next_token(lexer);
		free(tmp_tok->content);
		free(tmp_tok);
	}
	return (tmp);
}

void parse()
{
	t_lexer	*lexer = NULL;
	t_token	*token = NULL;

	g_global.flag = 0;
	quote_checker(g_global.line);	
	if (ft_strchr_parse(g_global.line, '$') == 1)
		if (g_global.flag != 1)
			g_global.line = ft_expand(g_global.line);
	if (g_global.line != NULL)
	{
		lexer = start_lexer(g_global.line);
		token  = next_token(lexer);
		g_global.cmds = ft_parce(lexer, token, &g_global.cmds);
		//print_cmd(g_global.cmds);
		free(lexer);
	}
}
