# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouliba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 14:30:37 by acouliba          #+#    #+#              #
#    Updated: 2021/11/11 16:03:35 by acouliba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILE =builtin_cd.c          builtin_exit.c        builtin_pwd.c         main.c                signal.c\
      builtin_echo.c        builtin_export.c      builtin_unset.c       run.c                 t_list_utils.c\
      builtin_env.c         builtin_export_part.c exec.c                run_part.c            termios.c

FILE_BONUS = exec.c  bonus.c     utils.c    run.c

LIBFT_DIRECTORY = libft/

PARSING_DIRECTORY = parse/

LIBFT = $(LIBFT_DIRECTORY)libft.a

LDFLAGS ="-L/opt/homebrew/opt/readline/lib"
CPPFLAGS ="-I/opt/homebrew/opt/readline/include"

#LDFLAGS="-L/goinfre/acouliba/brew/opt/readline/lib"
#CPPFLAGS="-I/goinfre/acouliba/brew/opt/readline/include"


FLAGS = -Wall -Wextra -Werror -fsanitize=address $(LDFLAGS) $(CPPFLAGS)

FLAGS =  $(LDFLAGS) $(CPPFLAGS)

HEADERS = includes

SOURCES_DIRECTORY = src/

OBJECTS_DIRECTORY = obj/

SRCS = $(addprefix $(SOURCES_DIRECTORY), $(FILE))

OBJS = $(addprefix $(OBJECTS_DIRECTORY), $(FILE:.c=.o))

OBJS_BONUS = $(addprefix $(OBJECTS_DIRECTORY), $(FILE_BONUS:.c=.o))


$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c
	gcc  $(FLAGS) -I $(HEADERS) -c $< -o $@

all:$(NAME)

bonus: $(NAME) $(OBJS_BONUS)
	gcc $(FLAGS) -I $(HEADERS) $(PRINTF) $(OBJS_BONUS) -o ${NAME}

$(LIBFT):
	@echo "make libft"
	@make -sC $(LIBFT_DIRECTORY)
	@make bonus -sC $(LIBFT_DIRECTORY)

$(OBJECTS_DIRECTORY):
	mkdir -p $@

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJS)
	gcc $(FLAGS) -I $(HEADERS) $(PRINTF) $(OBJS) $(LIBFT) $(PARSING_DIRECTORY)parse.a -lreadline -o $(NAME)


clean:
	rm -Rf $(OBJECTS_DIRECTORY)

fclean: clean
	@make fclean -sC $(LIBFT_DIRECTORY)
	@make fclean -sC $(PARSING_DIRECTORY)
	rm -f $(NAME)


re: ree all

ree: fclean
	@make re -sC $(LIBFT_DIRECTORY)
	@make bonus -sC $(LIBFT_DIRECTORY)
	@make test -sC $(PARSING_DIRECTORY)
	@make bonus -sC $(LIBFT_DIRECTORY)

exe: re
	@make test -sC $(PARSING_DIRECTORY)
	./minishell

.PHONY: all clean fclean re