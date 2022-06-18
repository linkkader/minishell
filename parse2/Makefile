
   
NAME = minishell

CC = cc


LDFLAGS ="-L/opt/homebrew/opt/readline/lib"
CPPFLAGS ="-I/opt/homebrew/opt/readline/include"

#LDFLAGS="-L/goinfre/acouliba/brew/opt/readline/lib"
#CPPFLAGS="-I/goinfre/acouliba/brew/opt/readline/include"

CFLAGS = $(LDFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror -fsanitize=address
CFLAGS = $(LDFLAGS) $(CPPFLAGS)

.PHONY = all clean fclean re

SRCS = check_for_error.c                          heredoc.c                                  libft/list/ft_lstsize.c                    libft/string/string.c\
       close_all.c                                libft/ft_calloc.c                          libft/string/ft_strjoin.c                  libft/string/wrap_with_space.c\
       expanding/expander.c                       libft/ft_itoa.c                            libft/string/puterror.c                    main.c\
       expanding/init.c                           libft/ft_realloc.c                         libft/string/split/clear.c                 open_pipes.c\
       expanding/utils.c                          libft/is_alnum.c                           libft/string/split/count_tokens.c          parser.c\
       get_command.c                              libft/list/create_node.c                   libft/string/split/replace_all_strings.c   remove_quotes.c\
       get_env.c                                  libft/list/ft_lst_clear.c                  libft/string/split/replace_inside_quotes.c tokenizer.c\
       get_infiles.c                              libft/list/ft_lstadd_back.c                libft/string/split/split.c\
       get_outfiles.c                             libft/list/ft_lstlast.c                    libft/string/split/tokens_length.c


OBJS :=$(SRCS:.c=.o)

all : $(NAME)

#$(NAME) : $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


$(NAME) :
	$(CC)  $(CFLAGS) -lreadline $(SRCS) -o $(NAME)


.c.o:
	gcc  $(CFLAGS) -c $< -o ${<:.c=.o}

test: $(SRCS) $(OBJS)
	ar rc parse.a $(OBJS)

clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all