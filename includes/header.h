/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <acouliba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:10:22 by acouliba          #+#    #+#             */
/*   Updated: 2022/06/21 18:00:14 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <dirent.h>
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
# include "../src/parce/minishell.h"

# define ERR_CMD ": command not found\n"
# define PROMPT_CMD "minishell$ "
# define NOT_AN_IDENTIFIER "minishell: export: %s: not a valid identifier"

//infile token
# define INFILE 2
# define OUTFILE 4
# define APPEND 1
# define HEREDOC 0



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
void	env_builtin(t_cmd *cmd);

t_cmd	*fake();
void	my_pipe(t_cmd *cmd);
void	exe(t_cmd *cmd);
char	*get_cmd_path(t_cmd *cmd, char *name);
void	push_entry(t_list **lst, char *str);
char	*ft_get_env(char *name);
t_entry	*to_entry(void *e);
void	free_entry(void *content);
void	clear_d2(char **cmd);
void	update_env();
void	put_error(char *str, char *error);
void	my_perror(int result, char *str);

void	sigint_handler_in_process(int sig);
void	sigquit_handler_in_process(int sig);
void	sigint_handler_nonl(int sig);
void	signals();
void	reset_signals();


void	correct_echo();
void	normal_echo();

int	infile(t_file *tFile, int in, int *error);
int	outfile(t_file *tFile, int out, int *error);
int append_file(t_file *tFile, int out, int *error);
int	here_doc(t_file *tFile, int in, int *error);


#endif
