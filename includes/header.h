/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:10:22 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:00:14 by acouliba         ###   ########.fr       */
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
#include <sys/errno.h>
# include "../libft/libft.h"

# define ERR_CMD ": command not found\n"
# define PROMPT_CMD "minishell$ "
# define NOT_AN_IDENTIFIER "minishell: export: %s: not a valid identifier"


typedef enum bool
{
	false,
	true
}	t_bool;

typedef struct entries{
	char	*key;
	char	*value;
	t_bool	is_exported;
}	t_entry;

typedef struct s_cmd
{
	int				doc_index;
	char			*path;
	int				in;
	int				out;
	char			**args;
	char			**infile;
	char			**outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_global
{
	t_cmd			*cmds;
	char			*line;
	char			**env;
	t_list			*entries;
	int				exit_code;
	struct termios	*attributes;
	sig_t			sig_int;
	sig_t			sig_quit;
}					t_global;

t_global g_global;

void	init(char **env);

void	exit_builtin(t_cmd *cmd);
void	cd_builtin(t_cmd *cmd);
void	echo_builtin(t_cmd *cmd);
void	check_builtin(t_cmd *tmp);
void	exit_builtin(t_cmd *cmd);
void	pwd_builtin(t_cmd *tmp);
void	export_builtin(t_cmd *cmd);
void	export_value(char *key, char *value, t_cmd *cmd, t_bool is_in_export);
void	unset_builtin(t_cmd *cmd);

//void	correct_echo(t_var *v);
void	push_entry(t_list **lst, char *str);
char	*ft_get_env(char *name);
t_entry	*to_entry(void *e);
void	free_entry(void *content);
void	clear_d2(char **cmd);
void	update_env();

//void	sigint_handler_in_process(int sig);
//void	sigquit_handler_in_process(int sig);
//void	sigint_handler_nonl(int sig);


//void	correct_echo(t_var *v);
//void	normal_echo(t_var *v);

#endif
