# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouliba <momeaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 14:30:37 by acouliba          #+#    #+#              #
#    Updated: 2022/06/21 17:39:40 by acouliba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FILE = builtin_cd.c          builtin_exit.c        builtin_pwd.c         main.c                signal.c\
       builtin_echo.c        builtin_export.c      builtin_unset.c       run.c                 t_list_utils.c\
       builtin_env.c         builtin_export_part.c exec.c                run_part.c            termios.c\
       builtin_export_part2.c	init_util.c

BUILTINS_DIRECTORY = builtins/

LIBFT_DIRECTORY = libft/

PARSING_DIRECTORY = parce/

BUILTINS_FILE = builtin_cd.c     builtin_echo.c   builtin_env.c    builtin_exit.c   builtin_export.c builtin_pwd.c    builtin_unset.c

FILE = check_builtins.c exe.c            get_path.c       init.c           main.c           signal.c         t_list_utils.c   termios.c error.c  fake.c  pipe.c fix_fd.c here_doc.c\

PARSE = $(PARSING_DIRECTORY)parse.a

LIBFT = $(LIBFT_DIRECTORY)libft.a

HEADERS = includes

SOURCES_DIRECTORY = src/

OBJECTS_DIRECTORY = obj/

FLAGS = -Wextra -Wall -Werror

FLAGS =

LDFLAGS= -L /opt/homebrew/opt/readline/lib
CPPFLAGS= -I /opt/homebrew/opt/readline/include

LDFLAGS="-L/goinfre/acouliba/brew/opt/readline/lib"
CPPFLAGS="-I/goinfre/acouliba/brew/opt/readline/include"

#LDFLAGS= -L /Users/momeaizi/Desktop/brew/opt/readline/lib
#CPPFLAGS= -I /Users/momeaizi/Desktop/brew/opt/readline/include

FLAGS = $(LDFLAGS) $(CPPFLAGS)

OBJS = $(addprefix $(OBJECTS_DIRECTORY), $(FILE:.c=.o)) $(addprefix $(OBJECTS_DIRECTORY)$(BUILTINS_DIRECTORY), $(BUILTINS_FILE:.c=.o))

OBJS_BONUS = $(addprefix $(OBJECTS_DIRECTORY), $(FILE_BONUS:.c=.o))

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c
	gcc  $(FLAGS) -I $(HEADERS) -c $< -o $@

all:$(NAME)

$(LIBFT):
	@echo "make $(LIBFT)"
	@make -sC $(LIBFT_DIRECTORY)
	@make bonus -sC $(LIBFT_DIRECTORY)

$(PARSE):
	@echo "make $(PARSE)"
	@make -sC $(PARSING_DIRECTORY)

$(OBJECTS_DIRECTORY):
	mkdir -p $@
	mkdir -p $(OBJECTS_DIRECTORY)$(BUILTINS_DIRECTORY)

#$(PARSE)

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJS) $(PARSE)
	gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) $(PARSE) $(LDFLAGS) -l readline  -o  $(NAME)


clean:
	rm -Rf $(OBJECTS_DIRECTORY)

fclean: clean
	rm -f $(NAME)
	@make fclean -sC $(LIBFT_DIRECTORY)
	#@make fclean -sC $(PARSING_DIRECTORY)

re: fclean all

.PHONY: all clean fclean re
