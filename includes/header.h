/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:10:22 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:00:14 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../parsing/minishell.h"

# define ERR_CMD ": command not found\n"
# define PROMPT_CMD "minishell$ "
# define NOT_AN_IDENTIFIER "minishell: export: %s: not a valid identifier"

typedef struct try_exec{
	char	*path;
	int		start;
}	t_try;

typedef struct var{
	int				in;
	int				out;
	t_try			*tr;
	t_list			*env;
	sig_t			sig_int;
	sig_t			sig_quit;
	int				console_fd;
	int				err;
	struct termios	*attributes;
	pid_t			*pids;
	t_command		*head;
	t_command		*previous;
}	t_var;

typedef enum bool
{
	true,
	false
}	t_bool;

typedef struct util
{
	int		i;
	int		j;
	t_var	*var;
	t_bool	bool;
	t_bool	is_in_export;
}	t_util;

typedef struct entries{
	char	*key;
	char	*value;
	t_bool	is_exported;
}	t_entry;

char	*read_line(int entry);
void	exec_doc(int *pdes, char *limit);
char	**check_cmd(t_var *v, t_command *head);
void	run_all(t_var *v);
int		to_pipe(int fd);
char	**split_string(char *s, char c);
void	exec(char **cmd);

void	echo_builtin(char **cmd, t_var *v);
void	cd_builtin(char **path, t_var *v);
void	pwd_builtin(char **cmd, t_var *v);
void	exit_builtin(char **cmd, t_var *v);
void	env_builtin(char **cmd, t_var *v);
void	export_builtin(char **cmd, t_var *v);
t_try	*ft_try_exec(t_var *var, char *name, int start);
void	not_an_identifier(t_var *var);
void	try_export_value(char **sp, t_var *var, t_bool is_in_export, int start);
void	export_value(char *key, char *value, t_var *var, t_bool is_in_export);
void	unset_builtin(char **cmd, t_var *v);
char	**to_env(t_list *list, t_bool real);
void	my_clear(char ***cmd);
char	*ft_get_env(t_var *var, char *name);

void	correct_echo(t_var *v);
void	push(t_list **lst, char *str);
t_entry	*to_entry(void *e);
void	free_entry(void *content);

void	sigint_handler_in_process(int sig);
void	sigquit_handler_in_process(int sig);
void	sigint_handler_nonl(int sig);


void	correct_echo(t_var *v);
void	normal_echo(t_var *v);

int		size_t_command(t_command *cmd);
void	reset_setting(t_var *var);

void	init_util(t_util *util, int start, t_var *var, t_bool is_in_export);
#endif
