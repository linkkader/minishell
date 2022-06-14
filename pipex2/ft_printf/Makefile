# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouliba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 14:30:37 by acouliba          #+#    #+#              #
#    Updated: 2021/11/26 17:14:16 by acouliba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = srcs/ft_isalnum.c		srcs/ft_itoa.c		srcs/ft_memset.c		srcs/ft_split.c		srcs/ft_strlcat.c	srcs/ft_strnstr.c		srcs/ft_toupper.c\
	   srcs/ft_isalpha.c		srcs/ft_memchr.c		srcs/ft_putchar_fd.c	srcs/ft_strchr.c		srcs/ft_strlcpy.c	srcs/ft_strrchr.c\
	   srcs/ft_atoi.c		srcs/ft_isascii.c	srcs/ft_memcmp.c		srcs/ft_putendl_fd.c	srcs/ft_strdup.c		srcs/ft_strlen.c		srcs/ft_strtrim.c\
	   srcs/ft_bzero.c		srcs/ft_isdigit.c	srcs/ft_memcpy.c		srcs/ft_putnbr_fd.c	srcs/ft_striteri.c	srcs/ft_strmapi.c	srcs/ft_substr.c	\
	   srcs/ft_calloc.c		srcs/ft_isprint.c	srcs/ft_memmove.c	srcs/ft_putstr_fd.c	srcs/ft_strjoin.c	srcs/ft_strncmp.c	srcs/ft_tolower.c\
	   srcs/ft_lstadd_back_bonus.c	srcs/ft_lstnew_bonus.c srcs/ft_lstclear_bonus.c	srcs/ft_lstiter_bonus.c	srcs/ft_lstnew_bonus.c	srcs/ft_lstlast_bonus.c\
       srcs/ft_lstadd_front_bonus.c	srcs/ft_lstdelone_bonus.c	srcs/ft_lstmap_bonus.c	srcs/ft_lstsize_bonus.c	ft_printf.c	ft_split2.c ft_atoi2.c\
       ft_utils.c	ft_utils2.c	ft_utils3.c	ft_utils4.c	ft_case.c	ft_case2.c

BONUS = srcs/ft_lstadd_back_bonus.c	srcs/ft_lstnew_bonus.c srcs/ft_lstclear_bonus.c	srcs/ft_lstiter_bonus.c	srcs/ft_lstnew_bonus.c	srcs/ft_lstlast_bonus.c\
		srcs/ft_lstadd_front_bonus.c	srcs/ft_lstdelone_bonus.c	srcs/ft_lstmap_bonus.c	srcs/ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

HEADERS = .

.c.o:
	gcc  ${FLAGS} -I $(HEADERS) -c $< -o ${<:.c=.o}

all: ${NAME}

bonus: all

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

clean:
	rm -f ${OBJS} ${OBJS_B}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
