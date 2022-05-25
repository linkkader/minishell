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
# include "ft_printf.h"

# define ERR_CMD "Command not found: "

typedef struct var{
	int		in;
	int		out;
	char	**env;
	char	**av;
	int		ac;
	int		length;
	char	**sp;
	char	*cmd[1000];
	pid_t	*pids;
}	t_var;

char	*read_line(int entry);
void	exec_doc(int *pdes, char *limit);
char	**check_cmd(t_var v, int index, int console);
void	run_all(int length, t_var *v, int start, int console_fd);
int		to_pipe(int fd);

#endif
