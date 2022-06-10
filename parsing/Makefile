

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

.PHONY = all clean fclean re

HEADERS = includes

SRCS = check_for_error.c close_all.c       get_command.c     get_env.c         get_infiles.c     get_outfiles.c    heredoc.c         main.c            open_pipes.c      parser.c          remove_quotes.c   tokenizer.c\
	expanding/expander.c expanding/init.c     expanding/utils.c\
	libft/ft_calloc.c  libft/ft_itoa.c    libft/ft_realloc.c libft/is_alnum.c\
	libft/list/create_node.c    libft/list/ft_lst_clear.c   libft/list/ft_lstadd_back.c libft/list/ft_lstlast.c     libft/list/ft_lstsize.c\
	libft/string/ft_strjoin.c      libft/string/puterror.c        libft/string/string.c          libft/string/wrap_with_space.c\
	libft/string/split/clear.c                 libft/string/split/replace_all_strings.c   libft/string/split/split.c\
    libft/string/split/count_tokens.c          libft/string/split/replace_inside_quotes.c libft/string/split/tokens_length.c


OBJS :=$(SRCS:.c=.o)

all : $(NAME)

#$(NAME) : $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


$(NAME) :
	$(CC) -I $(HEADERS)  -lreadline $(SRCS) -o $(NAME) exec.a

.c.o:
	gcc  ${FLAGS} -c $< -o ${<:.c=.o}

OBJS = $(SRCS:.c=.o)

test: $(SRCS) $(OBJS)
	ar rc parse.a ${OBJS}

clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all