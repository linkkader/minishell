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

char	*handle_quote(char *str, char *value, char q, int *i)
{
	(*i)++;
	while (value[(*i)] != q && value[(*i)] != '\0')
	{	
		str = ft_charjoin(str, value[(*i)]);	
		(*i)++;
	}
	if (value[(*i)] == q)
		(*i)++;
	else if (value[(*i)] == '\0')
	{
		write(2, "quote error\n", 13);
		free(g_global.line);
		g_global.line = NULL;
		return (NULL);
	}
	return (str);
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

char	*check_quote(char *value, int *flag)
{
	char *str;
	int i;

	i = 0;
	str = NULL;
	while (value[i] != '\0')
	{
		if (value[i] == '\"')
		{
			str = handle_quote(str, value, '\"', &i);}
		else if (value[i] == '\'')
		{
			str = handle_quote(str, value, '\'', &i);
			(*flag) = 1;
		}
		else
		{
			str = ft_charjoin(str, value[i]);
			i++;
		}
	}
	return (str);
}

void	check_last(int i)
{
	if (i != -1)
		if (i != 5)
			write(2, "syntax error\n", 14);
}


// void	print_cmd(t_cmd *data)
// {
// 	int i = 0;
// 	while(data)
// 	{
// 		while (data->file)
// 		{
// 			printf("token( %d) name (%s)\n", data->file->token, data->file->name);
// 			data->file = data->file->next;
// 		}
// 		i = 0;
// 		while(data->cmd && data->cmd[i])
// 		{
// 			printf("cmd :: %s\n", data->cmd[i]);
// 			i++;
// 		}
// 		printf("================\n");
// 		data = data->next;
// 	}
// }

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
	int 	i;

	i = -1;
	(*data) = malloc(sizeof(t_cmd));
	(*data)->file = NULL;
	(*data)->cmd = NULL;
	(*data)->next = NULL;
	tmp = (*data);
	while (token != NULL)
	{
		if (ft_check_error(token->type, token->content, &i, (*data)) == -1)
		{
			free_data(tmp);
			check_last(i);
			return NULL;
		}
		ft_pipe_(data, i);
		token = next_token(lexer);
	}
	
	return (tmp);
}

void parse()
{
	t_lexer	*lexer;
	t_token	*token;
	int flag;

	flag = 0;
	g_global.line = check_quote(g_global.line, &flag);
	if (ft_strchr_parse(g_global.line, '$') == 1 && flag == 0)
		g_global.line = ft_expand(g_global.line);

	if (g_global.line != NULL)
	{
		lexer = start_lexer(g_global.line);
		token  = next_token(lexer);
		g_global.cmds = ft_parce(lexer, token, &g_global.cmds);
		//print_cmd(g_global.cmds);
	}
	
}
