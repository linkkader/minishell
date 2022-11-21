CC = gcc

CFLAGS = -Wall -Wextra -Werror
CF = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

SRCS =	lexer_tools.c \
		lexer.c \
		ft_check.c \
		ft_error.c \
		minishell.c \
		ft_expand.c \
		utils.c \
		utils1.c \
		listing_tools.c \
		get_list.c

OBJS = ${SRCS:.c=.o}

NAME = minishell

REM = rm -f

all : $(NAME)
$(NAME) : $(OBJS)                                                     
	$(CC) $(CFLAGS) $(CF) $(OBJS) $(CFLAGS) -o $(NAME)

clean :
	${REM} ${OBJS}

fclean : clean
	${REM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
