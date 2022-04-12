/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:33:49 by apommier          #+#    #+#             */
/*   Updated: 2022/04/12 23:42:20 by apommier         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

// Command Data Structure

// Describes a simple command and arguments
typedef struct	s_simple {
	struct s_command	*big_cmd;
	int		fd[2];
	int		pipe[2];
	int		last;
	int 	last_pipe[2];
	int		child;
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
	char				**env;
	int					nb_s_cmd;
	struct	s_simple	**s_cmds;
	//char				*outfile;
	//char				*infile;
	int					err_var;
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

//free_cmd
void free_cmd(t_cmd *cmd);
void exit_shell(t_cmd *cmd);

//set_quote.c
int		is_in_quote(char *str, int index);
int		is_quote_good(char *str);
char	**ft_split_with_quote(char const *s, char c);

//redirection.c set redirection and input good
char	*set_redirection(t_s_cmd *cmd, char *line, int index);
char	next_space(char *str, int i);

//uitls redirection
int		parse_quote(t_cmd *cmd);
char	*get_str(char *str, int start, int end);
char	*cut_str(char *str, int start, int end);
int	double_size(char **tab);
void	print_double_fd(char **tab, int fd);
 void	free_double(char **tab);

//builtins utils
void	register_env(t_s_cmd *cmd, char *variable);
void	ft_env(t_s_cmd *cmd, char **env);
int		find_pwd(t_s_cmd *cmd);
void	init_s_cmd(t_s_cmd *cmd, char **env);
int		tab_len(char **tab);
int		find_len(char *input, int i, char c);
void	lone_export(t_s_cmd *cmd);
void	find_variable(char *variable, t_s_cmd *cmd);
int		find_it(char **str, char *s);

//real builtin
void	print_env(char **tab);
void	ft_env(t_s_cmd *cmd, char **env);
void	ft_exit(t_s_cmd *cmd);
void	ft_export(t_s_cmd *cmd);
void	ft_unset(t_s_cmd *cmd);
void	ft_echo(t_s_cmd *cmd);
void	ft_pwd(t_s_cmd *cmd);
void	open_directory(t_s_cmd *cmd);//cd

//parse builtin
int	is_builtin(char *cmd);
void	call_builtin(t_cmd *cmd);

#endif