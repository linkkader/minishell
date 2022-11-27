/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:33:04 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/26 21:05:06 by ofarissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"

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


typedef struct s_file
{
	int				fd;
	int				token;
	char			*name;
	struct s_file	*next;
}            t_file;

typedef struct s_cmd
{
	int				doc_index;
	char			*path;
	int				in;
	int				out;
	char			**cmd;
	t_file			*file;
	int				error;
	pid_t			pid;
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
	int				std_in;
	int				flag;
	int 			doc_here_status;
}					t_global;

t_global g_global;

typedef struct	s_token
{
	enum
	{
		HEREDOC,
		APPEND,
		INFILE,
		PIPE,
		OUTFILE,
		CMD,
	} type;
	char *content;
}	t_token;

typedef struct	s_lexer
{
	char	c;
	int		index;
	char	*value;
}	t_lexer;

/* ===================== PARISING ===================== */

void	parse();
t_lexer	*start_lexer(char *content);
t_token	*start_token(int type, char *content);
t_token	*move_token(t_lexer *lexer, t_token *token);
t_token	*next_token(t_lexer *lexer);
t_token	*collect_str(t_lexer *lexer);
t_token	*collect_app_here(t_lexer *, char c, int i);
t_file	*ft_lstlast_parse(t_file *lst);
t_file	*ft_lstnew_parse(int token, char *name);
void	skip_spaces(t_lexer *lexer);
void	move_byone(t_lexer *lexer);
char	*convert_char(t_lexer *lexer);
char	*ft_strdup_parse(char *s1);
int		ft_strlen_parse(char *str);
char	*handle_quote(t_lexer *lexer, char *value, char q);
char	*ft_strjoin_parse(char *s1, char *s2);
char	*ft_charjoin(char *s1, char c);
int		is_cmd(char c);
char	*check(t_lexer *lexer);
int		ft_check_error(int type, char *content, int *i, t_cmd *data);
int		check_infile(int *i);
int		check_outfile(int *i);
int		check_heredoc(int *i);
int		check_append(int *i);
int		check_pipe(int *i);
void	store_file(t_cmd *data, int i, char *content);
char	**store_cmd(char **tab, char *str);
char	*ft_substr_parse(char *s, unsigned int start, size_t len);
char	*ft_expand(char *value);
void	ft_lstadd_back_parse(t_file **lst, t_file *new);
t_cmd	*ft_last(t_cmd *lst);
t_cmd	*ft_new(t_file *file, char **cmd);
char	*ft_get_env(char *name);
int		ft_strchr_parse(char *s, int c);
char	*ft_itoa(int n);


#endif
