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

FILE = main.c run.c exec.c builtin.c builtin_export.c t_list_utils.c signal.c

FILE_BONUS = exec.c  bonus.c     utils.c    run.c

LIBFT_DIRECTORY = libft/

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
	gcc $(FLAGS) -I $(HEADERS) $(PRINTF) $(OBJS) $(LIBFT) parsing/parse.a -lreadline -o $(NAME)


clean:
	rm -Rf $(OBJECTS_DIRECTORY)

fclean: clean
	#@make fclean -sC $(LIBFT_DIRECTORY)
	rm -f $(NAME)


re: fclean all

ree: fclean
	@make re -sC $(LIBFT_DIRECTORY)
	@make bonus -sC $(LIBFT_DIRECTORY)
	@make fclean -sC parsing
	@make test -sC parsing
	@make bonus -sC $(LIBFT_DIRECTORY)

exe: re
	./minishell

.PHONY: all clean fclean re