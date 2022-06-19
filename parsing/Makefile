
   
NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror 

.PHONY = all clean fclean re

#LDFLAGS ="-L/opt/homebrew/opt/readline/lib"
#CPPFLAGS ="-I/opt/homebrew/opt/readline/include"

LDFLAGS="-L/goinfre/acouliba/brew/opt/readline/lib"
CPPFLAGS="-I/goinfre/acouliba/brew/opt/readline/include"

CFLAGS = $(LDFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror -fsanitize=address
CFLAGS = $(LDFLAGS) $(CPPFLAGS)


SRCS = check_for_error.c                          heredoc/get_line.c                         libft/list/ft_lstsize.c                    libft/string/wrap_with_space.c\
       cleaning.c                                 heredoc/heredoc.c                          libft/string/ft_strjoin.c                  main.c\
       close_all.c                                libft/ft_calloc.c                          libft/string/puterror.c                    open_pipes.c\
       expanding/expander.c                       libft/ft_itoa.c                            libft/string/split/clear.c                 parser.c\
       expanding/init.c                           libft/ft_realloc.c                         libft/string/split/count_tokens.c          remove_quotes.c\
       expanding/utils.c                          libft/is_alnum.c                           libft/string/split/replace_all_strings.c   signal_doc.c\
       get_command.c                              libft/list/create_node.c                   libft/string/split/replace_inside_quotes.c tokenizer.c\
       get_env.c                                  libft/list/ft_lst_clear.c                  libft/string/split/split.c\
       get_infiles.c                              libft/list/ft_lstadd_back.c                libft/string/split/tokens_length.c\
       get_outfiles.c                             libft/list/ft_lstlast.c                    libft/string/string.c

OBJS :=$(SRCS:.c=.o)

all : $(NAME)

#$(NAME) : $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	gcc  $(CFLAGS) -c $< -o ${<:.c=.o}

test: fclean $(SRCS) $(OBJS)
	ar rc parse.a $(OBJS)

$(NAME) :
	$(CC)  $(CFLAGS) -lreadline $(SRCS) -o $(NAME)
clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all