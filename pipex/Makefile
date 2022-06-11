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

NAME = pipex

FILE = exec.c  main.c     utils.c    run.c

FILE_BONUS = exec.c  bonus.c     utils.c    run.c

TMP = Test

PRINTF_DIRECTORY = ft_printf/

PRINTF = $(PRINTF_DIRECTORY)libftprintf.a

FLAGS = -Wall -Wextra -Werror

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
	gcc $(FLAGS) -I $(HEADERS) $(PRINTF) $(OBJS_BONUS) -lreadline -o ${NAME}

$(PRINTF):
	@echo "make ft_printf"
	@make -sC $(PRINTF_DIRECTORY)

$(OBJECTS_DIRECTORY):
	mkdir -p $@

$(NAME): $(PRINTF) $(OBJECTS_DIRECTORY) $(OBJS)
	gcc $(FLAGS) -I $(HEADERS) $(PRINTF) $(OBJS) -o ${NAME}

clean:
	@make fclean -sC $(PRINTF_DIRECTORY)
	rm -Rf $(OBJECTS_DIRECTORY)

fclean: clean
	rm -f $(NAME)

re: fclean all

exe: bonus
	 ./pipex ls "ls" "cat -e" 'cat -e' 'cat -e' 'cat -e' a1.out

.PHONY: all clean fclean re