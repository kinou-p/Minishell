/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:33:49 by apommier          #+#    #+#             */
/*   Updated: 2022/04/22 11:43:15 by apommier         ###   ########.fr       */
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

int	g_var;

// Command Data Structure

// Describes a simple command and arguments
typedef struct s_simple {
	struct s_command	*big_cmd;
	int					fd[2];
	int					pipe[2];
	int					last;
	int					last_pipe[2];
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
typedef struct s_command {
	int					tmpin;
	int					tmpout;
	char				**env;
	int					nb_s_cmd;
	struct s_simple		**s_cmds;
	int					err_var;
	struct s_simple		*current_s_cmd;
	char				**path;
}				t_cmd;

//main.c
int		main(int ac, char **av, char **path);
char	**ft_dup_double(char **env);

//pipe.c
void	execute(t_cmd *cmd);

//set_cmd.c
char	*error_parsing(char *to_free);
t_cmd	*set_cmd(char *input, char **path, int nb);

//exec_utils.c
int		wait_exit(t_cmd *cmd);
void	exit_child(t_cmd *cmd, int exit_pid, int status, int i);
void	check_access(t_cmd *cmd);
void	close_pipe(t_cmd *cmd);

//pipex_utils.c
void	set_fdin(t_cmd *cmd, int *fdin);
void	reset_fds(t_cmd *cmd);
char	**get_path(char **env);
char	*get_command(char **exec, char **env);

//free_cmd
void	free_cmd(t_cmd *cmd);
void	exit_shell(t_cmd *cmd, int ret);

//set_quote.c
char	*set_var(t_cmd *big_cmd, char *cmd);
int		is_in_quote(char *str, int index);
int		is_quote_good(char *str);
char	**ft_split_with_quote(char const *s, char c);

//signals
void	crtl_c(int num);
void	sig_heredoc(int num);
void	sig_quit(int num);

//redirection.c set redirection and input good
char	*get_word(char *str, int start);
char	**add_line(char **tab, char *line);
char	*set_redirection(t_s_cmd *cmd, char *line, int index, int i);
char	next_space(char *str, int i);

//set_heredoc
int		wait_prompt(t_s_cmd *cmd, int index, int i, char *input);

//heredoc_utils.c
void	sig_heredoc(int num);
int		free_wait_prompt(char *in, char**history);
void	change_signal(void);
void	sig_heredoc(int num);
char	**fill_history(t_s_cmd *cmd, char *input, char *in, char **history);

//set_input.c
char	*ft_input(char *line, t_s_cmd *cmd, int index);

//set_output.c
char	*ft_output(char *line, t_s_cmd *cmd, int index);

//set_var.c
char	*set_var(t_cmd *big_cmd, char *cmd);

//set_signals.c

//utils redirection
int		parse_quote(t_cmd *cmd);
char	*get_str(char *str, int start, int end);
char	*cut_str(char *str, int start, int end);
int		double_size(char **tab);
void	print_double_fd(char **tab, int fd);
void	free_double(char **tab);

//builtins utils
void	ft_shlvl(char **env);
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
int		size_path(char **str);
int		check_return(t_s_cmd *cmd, int var);
void	change_oldpwd(char **env, int old_pwd, int pwd, char *p);

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
int		is_builtin(char *cmd);
void	call_builtin(t_cmd *cmd);

#endif