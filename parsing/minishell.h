/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:52:11 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/06 19:15:48 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>

typedef struct s_token
{
	char	**tokens;
	char	*line;
	char	**limiters;
	int		index;
	char	should_expand;
}	t_token;

typedef struct s_command
{
	char				should_execute;
	char				*command_name;
	char				*command_path;
	char				**command_args;
	int					input;
	int					output;
	t_token				*tokens;
	struct s_command	*next;
}	t_command;

//					string
int			parse_ft_strlen(char *str);
void		parse_ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			parse_ft_strcmp(const char *s1, const char *s2);
int			puterror(char *name, char *error);
char		*strjoin(char *s1, char *s2);
char		*parse_ft_strdup(char *s1);
char		*wrap_redirection_by_space(char *str);
//					split
void		split(char ***tokens, char *s, char c);
int			count_tokens(char *str, char c);
int			*tokens_length(char *str, char c);
void		replace_inside_quotes(char *str, char new, char old);
void		replace_all_strings(char **strs, char new, char old);
void		clear(char **paths, int j);
//					list
t_command	*parse_ft_lstlast(t_command *lst);
void		parse_ft_lstadd_back(t_command **lst, t_command *new);
void		parse_ft_lstclear(t_command **head);
int			parseft_lstsize(t_command *cmds);
t_command	*create_node(t_command **head, char *line);
//					tokenizer
t_command	*tokenizer(char *str);


void	parser(t_command *cmds, int ***pipes, char **env);

char	**ft_realloc(char **ptr, char *new);
int		ftparse__isalpha(char c);
int		ft_isnum(char c);
int		parse_ft_isalnum(char c);
char	*ft_itoa(int n);
int		parse_ft_strncmp(const char *s1, const char *s2, size_t n);
char	*parse_ft_getenv(char *var, char **env);
char	*expand_var(char *str, char **env, char expand_all);
char	*remove_quotes(char *str);



//
void	get_cmds(t_command *commands, char **env);
void    heredoc(t_command *cmds, char **env);
void    get_infiles(t_command *cmds, char **env);
void    get_outfiles(t_command *cmds, char **env);
int		redirect(char *token);


int		check_quotes(char *str);
int		check_redirect(t_command *commands);


void	*ft_calloc(size_t count, size_t size);


void	clear_tokens(t_command **head);
void    open_pipes(t_command *cmds, int ***pipes);
void    close_all(t_command *cmds, int ***pipes);

void	cleaning(t_command **cmds, int ***pipes);
#endif