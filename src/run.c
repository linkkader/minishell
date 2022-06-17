/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:18 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/17 20:09:36 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void clear_pipe(int fd)
{
	char	c;

	while (read(fd, &c, 1))
	{
	}
}

void	my_clear(char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[0] && cmd[0][i])
		free(cmd[0][i++]);
	if (cmd[0])
		free(cmd[0]);
}

static pid_t	run(char *path, char **arg, t_var *v, t_command *cmd, int in, int *out)
{
	int		pdes[2];
	pid_t	child;


	pipe(pdes);
	child = fork();
	if (child == -1)
		perror("Pipe");
	else if (child == 0)
	{
		if (cmd->next)
			dup2(pdes[1], STDOUT_FILENO);
		else
			dup2(v->out, STDOUT_FILENO);
		dup2(in, STDIN_FILENO);
		close(pdes[0]);
		execve(path, arg, NULL);
		exit(0);
	}


	close(pdes[1]);
	cmd->output = dup(pdes[0]);

	return child;
}

void	exe(t_command *tmp, char **env)
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


void	sigint_handler_in_process(int sig)
{
	(void) sig;
	printf("\n");
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	printf("Quit: %d\n", sig);
}

char	**to_env(t_list *list)
{
	t_entry 	*entry;
	char 		**env;
	int 		i;
	char 		*temp;

	i = 0;
	env = malloc((ft_lstsize(list) + 1) * sizeof(char *));
	if (env == NULL)
	{
		//exit here
		return (NULL);
	}
	while (list)
	{
		entry = to_entry(list->content);
		if (entry->is_exported == false || entry->value == NULL)
		{
			list = list->next;
			continue;
		}
		temp = ft_strjoin(entry->key, "=");
		if (temp == NULL)
		{
			//exit here
			return (NULL);
		}
		env[i] = ft_strjoin(temp,entry->value);
		if (env[i] == NULL)
		{
			//exit here
			return (NULL);
		}
		free(temp);
		if (env[i] == NULL)
			return (NULL);
		i++;
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}


void correct_echo(t_var *v)
{
	struct termios attributes;

	if (v->attributes == NULL)
	{
		v->attributes = malloc(sizeof(struct termios));
		if (v->attributes == NULL)
		{
			//exit here
		}
		tcgetattr(STDIN_FILENO, v->attributes);
	}
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~~(ECHO | IEXTEN);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	//tcsetattr(STDIN_FILENO, TCSAFLUSH, &v->attributes);
}

void normal_echo(t_var *v)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, v->attributes);
}

void	run_all(t_var *v)
{
	t_command	*temp;
	char		**args;
	char		**env;
	int 		i;
	sig_t		sig[2];

	temp = v->head;
	env = to_env(v->env);
	i = 0;
	sig[0] = signal(SIGINT, sigint_handler_in_process);
	sig[1] = signal(SIGQUIT, sigquit_handler_in_process);
	normal_echo(v);
	while (temp)
	{
		v->out = temp->output;
		args = check_cmd(v, temp);
		if (args != NULL)
		{
			v->pids[i] = fork();
			if (!v->pids[i])
			{
				dup2(temp->input, 0);
				dup2(temp->output, 1);
				if (temp->input != 0)
					close(temp->input);
				if (temp->output != 1)
					close(temp->output);
				if (temp->should_execute)
					if (execve(temp->command_path, temp->command_args, env) == -1)
						exit (1/*puterror("", strerror(errno))*/);
				exit (2);
			}
		}
		if (temp->input != 0)
			close(temp->input);
		if (temp->output != 1)
			close(temp->output);
		i++;
		temp = temp->next;
	}
	while (i > -1)
		waitpid(v->pids[i--], NULL, 0);
	my_clear(&env);
	signal(SIGINT, sig[0]);
	signal(SIGQUIT, sig[1]);
	correct_echo(v);
}
