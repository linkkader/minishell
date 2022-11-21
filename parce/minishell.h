/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:33:04 by ofarissi          #+#    #+#             */
/*   Updated: 2022/11/21 15:54:47 by ofarissi         ###   ########.fr       */
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
		T_EOF
	} type;
	char *content;
}	t_token;

typedef struct	s_lexer
{
	char	c;
	int		index;
	char	*value;
}	t_lexer;

typedef struct s_file
{
	int				token;
	char			*name;
	struct s_file	*next;
}		t_file;

typedef struct s_cmd
{
	char			**cmd;
	t_file			*file;
	struct s_cmd	*next;
}		t_cmd;

/* ===================== PARISING ===================== */

t_lexer	*start_lexer(char *content);
t_token	*start_token(int type, char *content);
t_token	*move_token(t_lexer *lexer, t_token *token);
t_token	*next_token(t_lexer *lexer);
t_token	*collect_str(t_lexer *lexer);
t_token	*collect_app_here(t_lexer *, char c, int i);
t_file	*ft_lstlast(t_file *lst);
t_file	*ft_lstnew(int token, char *name);
void	skip_spaces(t_lexer *lexer);
void	move_byone(t_lexer *lexer);
char	*convert_char(t_lexer *lexer);
char	*ft_strdup(char *s1);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*handle_quote(t_lexer *lexer, char *value, char q);
int		is_cmd(char c);
int		ft_strchr(char *s, int c);
int		check_quote(char *str, int i);
char	*check(t_lexer *lexer);
int		ft_check_error(int type, char *content, int *i, t_cmd *data);
int		check_infile(int *i);
int		check_outfile(int *i);
int		check_heredoc(int *i);
int		check_append(int *i);
int		check_pipe(int *i);
void	store_file(t_cmd *data, int i, char *content);
char	**store_cmd(char **tab, char *str);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_expand(char *value);
void	ft_lstadd_back(t_file **lst, t_file *new);
void	ft_lstadd_back(t_file **lst, t_file *new);
void	ft_pipe(t_cmd **lst, t_cmd *new);
t_cmd	*ft_last(t_cmd *lst);
t_cmd	*ft_new(t_file *file, char **cmd);


#endif
