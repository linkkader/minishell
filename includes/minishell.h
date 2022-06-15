/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:10:22 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/17 20:11:30 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../libft/libft.h"
#include "../parse/minishell.h"

# define ERR_CMD "Command not found: "
# define PROMPT_CMD "minishell$ "
# define NOT_AN_IDENTIFIER "minishell: export: %s: not a valid identifier"

typedef struct var{
	int				in;
	int				out;
	t_list			*env;
	int 			console_fd;
	struct termios	attributes;
	pid_t			*pids;
	t_command		*head;
}	t_var;

typedef enum bool
{
	true,
	false
}	t_bool;


typedef struct entries{
	char	*key;
	char 	*value;
	t_bool	is_exported;
}	t_entry;


void	signals(void);

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
void	try_export_value(char **sp, t_var *var,t_bool is_in_export, int start);
void	unset_builtin(char **cmd, t_var *v);
char	**to_env(t_list *list);
void	my_clear(char ***cmd);

void	correct_echo(t_var *v);
void	push(t_list **lst, char *str);
t_entry	*to_entry(void *e);


#endif
