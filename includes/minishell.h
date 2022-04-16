/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:33:49 by apommier          #+#    #+#             */
/*   Updated: 2022/04/16 16:10:54 by apommier         ###   ########.fr       */
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
	int					fd[2];
	int					pipe[2];
	int					last;
	int 				last_pipe[2];
	int					child;
	int					nb_args;
	char				*infile;
	int					in_type;
	int					out_type;
	char				*outfile;
	char				**args;
	char				*cmd;
}				t_s_cmd;

// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
typedef struct	s_command {
	int					tmpin;
	int					tmpout;
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
char	**ft_dup_double(char **env);

//pipe.c
void	execute(t_cmd *cmd, char **env);

//set_cmd.c
t_cmd	*set_cmd(char *input, char **path, int nb);

//pipex_utils.c
char	**get_path(char **env);
char	*get_command(char **exec, char **env);

//free_cmd
void free_cmd(t_cmd *cmd);
void exit_shell(t_cmd *cmd, int ret);

//set_quote.c
char	*set_var(t_cmd *big_cmd, char *cmd);
int		is_in_quote(char *str, int index);
int		is_quote_good(char *str);
char	**ft_split_with_quote(char const *s, char c);

//signals
void crtl_c(int num);
void	sig_heredoc(int num);

//redirection.c set redirection and input good
char	*set_redirection(t_s_cmd *cmd, char *line, int index);
char	next_space(char *str, int i);

//uitls redirection
int		parse_quote(t_cmd *cmd);
char	*get_str(char *str, int start, int end);
char	*cut_str(char *str, int start, int end);
int		double_size(char **tab);
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
int		find_variable(char *variable, t_s_cmd *cmd);
int		find_it(char **str, char *s);
int		check_variable(char *variable);
int		cd_error(t_s_cmd *cmd, char *str, int i);
int		msg_error(t_s_cmd *cmd, char *cm, char *entry, char *error, int i);
int		size_path(char **str);
int		check_return(t_s_cmd *cmd, int var);

//real builtin
void	ft_exit(t_s_cmd *cmd);
int		print_env(t_cmd *cmd);
void	ft_env(t_s_cmd *cmd, char **env);
void	ft_exit(t_s_cmd *cmd);
int		ft_export(t_s_cmd *cmd);
int		ft_unset(t_s_cmd *cmd);
int		ft_echo(t_s_cmd *cmd);
int		ft_pwd(t_s_cmd *cmd);
int		open_directory(t_s_cmd *cmd);//cd

//parse builtin
int	is_builtin(char *cmd);
void	call_builtin(t_cmd *cmd);

#endif