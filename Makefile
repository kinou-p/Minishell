# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 12:50:24 by apommier          #+#    #+#              #
#    Updated: 2022/04/20 17:39:51 by sadjigui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
SRCS	= srcs/main.c\
		srcs/pipe/execution.c\
		srcs/pipe/pipex_utils.c\
		srcs/pipe/exec_utils.c\
		srcs/set_cmd/free_cmd.c\
		srcs/set_cmd/set_cmd.c\
		srcs/set_cmd/set_cmd_utils.c\
		srcs/set_redirection/redirection.c\
		srcs/set_redirection/utils.c\
		srcs/set_redirection/set_heredoc.c\
		srcs/set_redirection/heredoc_utils.c\
		srcs/set_redirection/set_input.c\
		srcs/set_redirection/set_output.c\
		srcs/built_in/unset.c\
		srcs/built_in/cd.c\
		srcs/built_in/cd_utils.c\
		srcs/built_in/echo.c\
		srcs/built_in/export.c\
		srcs/built_in/utils_builtin.c\
		srcs/built_in/init_builtin.c\
		srcs/built_in/export2.c\
		srcs/built_in/env.c\
		srcs/built_in/exit.c\
		srcs/built_in/choose_builtin.c\
		srcs/set_quote/split_with_quote.c\
		srcs/set_quote/set_quote.c\
		srcs/set_signals/set_signal.c\
		srcs/set_quote/set_var.c\
		
OBJS	= ${SRCS:.c=.o}
CC		= clang
CFLAGS	= -Wall -Wextra -g
LIB		= -lreadline
RM		= rm -rf
LIBFT	= ./libft

#-include ./valgrind.mk

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


