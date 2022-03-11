# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 12:50:24 by apommier          #+#    #+#              #
#    Updated: 2022/03/11 16:35:32 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRCS	= srcs/main.c\
		srcs/pipe/pipe.c\
		srcs/pipe/pipex_utils.c\
		srcs/set_cmd/free_cmd.c\
		srcs/set_cmd/set_cmd.c\
		srcs/set_redirection/redirection.c\
		srcs/set_redirection/utils.c
OBJS	= ${SRCS:.c=.o}
CC		= clang
CFLAGS	= -Wall -Wextra
LIB		= -lreadline
#CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
LIBFT	= ./libft

${NAME}: ${OBJS}
		@make bonus -C ${LIBFT}
		@${CC} ${LIB} ${OBJS} ${LIBFT}/libft.a -o ${NAME} 

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