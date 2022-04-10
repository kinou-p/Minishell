# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 12:50:24 by apommier          #+#    #+#              #
#    Updated: 2022/04/10 21:11:14 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRCS	= srcs/main.c\
		srcs/pipe/pipe.c\
		srcs/pipe/pipex_utils.c\
		srcs/set_cmd/free_cmd.c\
		srcs/set_cmd/set_cmd.c\
		srcs/set_redirection/redirection.c\
		srcs/set_redirection/utils.c\
		srcs/built_in/unset.c\
		srcs/built_in/cd.c\
		srcs/built_in/echo.c\
		srcs/built_in/export.c\
		srcs/built_in/utils_builtin.c\
		srcs/built_in/init_builtin.c\
		srcs/built_in/export2.c\
		srcs/built_in/env.c\
		srcs/set_quote/set_quote.c\
		srcs/set_quote/split_with_quote.c\
		srcs/built_in/choose_builtin.c
OBJS	= ${SRCS:.c=.o}
CC		= clang
CFLAGS	= -Wall -Wextra -g
LIB		= -lreadline
#CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
LIBFT	= ./libft

${NAME}: ${OBJS}
		@make bonus -C ${LIBFT}
		@${CC} ${LIB} ${OBJS} ${LIBFT}/libft.a -o ${NAME} 

all:	${NAME}

clean:
		@${RM} ${OBJS}
		@make clean -C ${LIBFT}

fclean:	clean
		@${RM} ${NAME}
		@make fclean -C ${LIBFT}

re: 	fclean all

.PHONY: all clean fclean re

-include ./valgrind.mk
