# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofarissi <ofarissi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 14:30:37 by acouliba          #+#    #+#              #
#    Updated: 2022/11/22 23:45:10 by ofarissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BUILTINS_DIRECTORY = builtins/

LIBFT_DIRECTORY = libft/

PARSING_DIRECTORY = parce/

PARSING_FILE = lexer_tools.c \
               		lexer.c \
               		ft_check.c \
               		ft_error.c \
               		minishell.c \
               		ft_expand.c \
               		utils.c \
               		utils1.c \
               		listing_tools.c \
               		get_list.c\
               		ft_free.c


BUILTINS_FILE = builtin_cd.c     builtin_echo.c   builtin_env.c    builtin_exit.c   builtin_export.c builtin_export_part.c builtin_pwd.c    builtin_unset.c

FILE = check_builtins.c exe.c            get_path.c       init.c      signal.c            t_list_utils.c   termios.c error.c  pipe.c fix_fd.c here_doc.c main.c part.c\

LIBFT = $(LIBFT_DIRECTORY)libft.a

HEADERS = includes

SOURCES_DIRECTORY = src/

OBJECTS_DIRECTORY = obj/

FLAGS =  -Wall -Wextra -Werror $(CPPFLAGS) -fsanitize=address -g

LDFLAGS="-L/goinfre/acouliba/brew/opt/readline/lib"
CPPFLAGS="-I/goinfre/acouliba/brew/opt/readline/include"

OBJS = $(addprefix $(OBJECTS_DIRECTORY), $(FILE:.c=.o)) $(addprefix $(OBJECTS_DIRECTORY)$(BUILTINS_DIRECTORY), $(BUILTINS_FILE:.c=.o)) $(addprefix $(OBJECTS_DIRECTORY)$(PARSING_DIRECTORY), $(PARSING_FILE:.c=.o))

OBJS_BONUS = $(addprefix $(OBJECTS_DIRECTORY), $(FILE_BONUS:.c=.o))

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c
	gcc  $(FLAGS) -I $(HEADERS) -c $< -o $@

all:$(NAME)

$(LIBFT):
	@echo "make $(LIBFT)"
	@make -sC $(LIBFT_DIRECTORY)
	@make bonus -sC $(LIBFT_DIRECTORY)




$(OBJECTS_DIRECTORY):
	mkdir -p $@
	mkdir -p $(OBJECTS_DIRECTORY)$(BUILTINS_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(PARSING_DIRECTORY)



$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJS)
	gcc $(FLAGS) -I $(HEADERS) $(OBJS)  $(LIBFT) $(LDFLAGS) $(CPPFLAGS) -l readline  -o  $(NAME)


clean:
	rm -Rf $(OBJECTS_DIRECTORY)
	@make clean -sC $(LIBFT_DIRECTORY)


fclean: clean
	rm -f $(NAME)
	@make fclean -sC $(LIBFT_DIRECTORY)

re: fclean all

.PHONY: all clean fclean re
