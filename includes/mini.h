/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:00:38 by sadjigui          #+#    #+#             */
/*   Updated: 2022/03/01 17:12:12 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_struct {
	char	**envy;
}				t_struct;

int		find_len(char *input, int i);
int		check_variable(char *variable);

void	normal();
void	red();
void	lexer(char *input, t_struct *data);
void	print_env(t_struct *data);
void	init_struct(t_struct *data, char **env);
void	ft_env(t_struct *data, char **env);
void	ft_exit(t_struct *data);
void	ft_export(char *input, t_struct *data);
void	ft_export_variable(t_struct *data, char *variable);
void	register_env(t_struct *data, char **variable);
void	free_char_tab(char **libre);
void	join_variable(t_struct *data, char **v_v, int size);

char	*check_value(char *value);
char	*define_value(char *value);

#endif
