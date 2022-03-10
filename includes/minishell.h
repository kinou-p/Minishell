/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:33:49 by apommier          #+#    #+#             */
/*   Updated: 2022/03/10 11:39:08 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>

// Command Data Structure

// Describes a simple command and arguments
typedef struct	s_simple {
	int		nb_args;
	char	*infile;
	int		in_type;
	int		out_type;
	char	*outfile;
	char	**args;
	char	*cmd;
}				t_s_cmd;

// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
typedef struct	s_command {
	int					nb_s_cmd;
	struct	s_simple	**s_cmds;
	char				*outfile;
	char				*infile;
	char				*err_file;
	struct	s_simple	*current_s_cmd;
	char				**path;
}						t_cmd;

//main.c
int	main();//int ac, char **av, char **path);

//pipe.c
void	execute(t_cmd *cmd, char **env);

//set_cmd.c
t_cmd	*set_cmd(char *input, char **path);

//pipex_utils.c
char	**get_path(char **env);
char	*get_command(char **exec, char **env);
void	print_double(char **tab);
void	free_double(char **tab);

//free_cmd
void free_cmd(t_cmd *cmd);
void exit_shell(t_cmd *cmd);

//redirection.c set redirection and input good
char	*set_redirection(t_s_cmd *cmd, char *line);
char	next_space(char *str, int i);

#endif