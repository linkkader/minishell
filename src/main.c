/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:55:30 by acouliba          #+#    #+#             */
/*   Updated: 2022/05/24 14:55:39 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init(char **env, t_var *var)
{
	int		index;

	index = 0;
	var->env = NULL;
	while (env[index])
	{
		push(&var->env, env[index]);
		index++;
	}
	var->console_fd = 2;
}

static int size_t_command(t_command *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

static void	exe(t_var *v)
{
	int		i;

	v->pids = malloc((size_t_command(v->head)) * sizeof(pid_t));
	if (v->pids == NULL)
	{
		//exit here
	}
	i = -1;
	if (v->pids == NULL)
		return ;
	run_all(v);
}

void free_entry(void *content)
{
	t_entry	*entry;

	entry = to_entry(content);
	if (entry->value != NULL)
		free(entry->value);
	if (entry->key != NULL)
		free(entry->key);
	free(content);
}

void	exe1(t_command *tmp, char **env)
{
	int	id;

	while (tmp)
	{
		id = fork();
		if (!id)
		{
			dup2(tmp->input, 0);
			dup2(tmp->output, 1);
			if (tmp->input != 0)
				close(tmp->input);
			if (tmp->output != 1)
				close(tmp->output);
			if (tmp->should_execute)
				if (execve(tmp->command_path, tmp->command_args, env) == -1)
					exit (1/*puterror("", strerror(errno))*/);
			exit (2);
		}
		wait(NULL);
		if (tmp->input != 0)
			close(tmp->input);
		if (tmp->output != 1)
			close(tmp->output);
		tmp = tmp->next;
	}
}

int		main(int ac, char **av, char **env)
{
	char		*str;
	t_var		v;
	int			**pipes;
	t_command	*head;
	char 		**temp_env;

	signals();
	v.attributes = NULL;
	correct_echo(&v);
	init(env, &v);
	while (1)
	{
		v.pids = NULL;
		head  = NULL;
		str = readline(PROMPT_CMD);
		if (str != NULL && ft_strlen(str) == 0)
		{
			free(str);
			continue;
		}
		if (str == NULL)
		{
			ft_putstr_fd(PROMPT_CMD, 1);
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		head  = NULL;
		add_history(str);
		temp_env = to_env(v.env);
		if (check_quotes(str) && ft_strlen(str))
		{
			head = tokenizer(str);
			if (check_redirect(head))
			{
				parser(head, &pipes,env);
			//	exe1(head, env);
			}
			//
			//cleaning(&head, &pipes);
		}
		v.head = head;
		free(v.pids);
		exe(&v);
		free(str);
		////ft_lstclear(&v.env, &free_entry);
		my_clear(&temp_env);
		cleaning(&head, &pipes);
		system("leaks minishell");
	}
	return (0);
}
