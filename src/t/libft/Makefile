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

NAME = libft.a

SRCS = ft_isalnum.c		ft_itoa.c		ft_memset.c		ft_split.c		ft_strlcat.c	ft_strnstr.c		ft_toupper.c\
	   ft_isalpha.c		ft_memchr.c		ft_putchar_fd.c	ft_strchr.c		ft_strlcpy.c	ft_strrchr.c\
	   ft_atoi.c		ft_isascii.c	ft_memcmp.c		ft_putendl_fd.c	ft_strdup.c		ft_strlen.c		ft_strtrim.c\
	   ft_bzero.c		ft_isdigit.c	ft_memcpy.c		ft_putnbr_fd.c	ft_striteri.c	ft_strmapi.c	ft_substr.c	\
	   ft_calloc.c		ft_isprint.c	ft_memmove.c	ft_putstr_fd.c	ft_strjoin.c	ft_strncmp.c	ft_tolower.c

BONUS = ft_lstadd_back_bonus.c	ft_lstnew_bonus.c ft_lstclear_bonus.c	ft_lstiter_bonus.c	ft_lstnew_bonus.c	ft_lstlast_bonus.c\
		ft_lstadd_front_bonus.c	ft_lstdelone_bonus.c	ft_lstmap_bonus.c	ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

HEADERS = .

.c.o:
	gcc  ${FLAGS} -I $(HEADERS) -c $< -o ${<:.c=.o}

all: ${NAME}

bonus: $(OBJS_B)
	ar rc ${NAME} ${OBJS_B}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

clean:
	rm -f ${OBJS} ${OBJS_B}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
