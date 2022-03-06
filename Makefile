# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 12:50:24 by apommier          #+#    #+#              #
#    Updated: 2022/03/06 16:59:33 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
SRCS	= main.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc
#CFLAGS	= -Wall -Wextra
LIB		= -lreadline
#CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
LIBFT	= ./libft

${NAME}: ${OBJS}
		@make bonus -C ${LIBFT}
		@${CC} ${CFLAGS} ${OBJS} ${LIBFT}/libft.a ${LIB} -o ${NAME}

all:	${NAME} bonus

clean:
		@${RM} ${OBJS}
		@make clean -C ${LIBFT}

fclean:	clean
		@${RM} ${NAME}
		@make fclean -C ${LIBFT}

re: 	fclean all

.PHONY: all clean fclean re bonus

-include ./valgrind.mk