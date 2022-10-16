NAME = parse.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

.PHONY = all clean fclean re

CFLAGS = $(LDFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror -fsanitize=address
CFLAGS = $(LDFLAGS) $(CPPFLAGS)


SRCS = error/check_for_error.c                    libft/list/ft_lstsize.c                    libft/string/wrap_with_space.c\
       clear/cleaning.c                           input/heredoc.c                            libft/string/ft_strjoin.c\
       clear/close_all.c                          libft/ft_calloc.c                          libft/string/puterror.c                    pipes/open_pipes.c\
       expanding/expander.c                       libft/ft_itoa.c                            libft/string/split/clear.c                 parser.c\
       expanding/init.c                           libft/ft_realloc.c                         libft/string/split/count_tokens.c          quotes/remove_quotes.c\
       expanding/utils.c                          libft/is_alnum.c                           libft/string/split/replace_all_strings.c   input/signal_doc.c\
       cmd_args/get_command.c                              libft/list/create_node.c                   libft/string/split/replace_inside_quotes.c tokenizer.c\
       get_env.c                                  libft/list/ft_lst_clear.c                  libft/string/split/split.c\
       input/get_infiles.c                        libft/list/ft_lstadd_back.c                libft/string/split/tokens_length.c\
       output/get_outfiles.c                      libft/list/ft_lstlast.c                    libft/string/string.c                      quotes/is_there_any_quotes.c

OBJS :=$(SRCS:.c=.o)

all : $(NAME)

.c.o:
	gcc -c $< -o ${<:.c=.o}

test: fclean $(SRCS) $(OBJS)
	ar rc $(NAME) $(OBJS)

$(NAME) :$(SRCS) $(OBJS)
	ar rc $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all