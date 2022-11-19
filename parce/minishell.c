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

void	ft_free(t_cmd *data)
{
	t_cmd *tmp;
	int i = 0;

	tmp = data;
	while(data)
	{
		while (data->file)
		{
			free(data->file->name);
			free(data->file);
			data->file = data->file->next;
		}
		i = 0;
		while(data->cmd && data->cmd[i])
		{
			free(data->cmd[i]);
			i++;
		}
		data = data->next;
		//free(data->cmd);
	}
	free(tmp);

}

void	print_data(t_cmd *data)
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
		// printf("token (%d) ====== name (%s)\n", token->type, token->content);
		if (ft_check_error(token->type, token->content, &i, (*data)) == -1)
			break ;
		ft_pipe_(data, i);
		token  = next_token(lexer);
	}
	return (tmp);
}
 
int main()
{
	t_lexer	*lexer;
	t_token	*token;
	t_cmd	*data;
	char 	*str;

	data = NULL;
	str = NULL;
	while(1)
	{
		str = readline("minishell> ");
		if (!str)
			exit(0);
		lexer = start_lexer(str);
		token  = next_token(lexer);
		data = ft_parce(lexer, token, &data);	
		print_data(data);
	}
}
