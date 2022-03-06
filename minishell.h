/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   minishell.h	:+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: apommier <apommier@student.42.fr>	  +#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2022/03/06 12:49:28 by apommier	  #+#	#+#	 */
/*   Updated: 2022/03/06 12:57:24 by apommier	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

// Command Data Structure

// Describes a simple command and arguments
typedef struct	s_simple {
	int		nb_args;
	char	**args;
	char	*cmd;
}				t_simple_cmd;

// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
typedef struct	s_command {
	int					nb_s_cmd;
	struct	s_simple	**simple_cmds;
	char				*out_file;
	char				*input_file;
	char				*err_file;
	int					background;
	struct s_command	*current_cmd;
	struct	s_simple	*current_s_cmd;
}						t_cmd;

//main.c
int	main(int ac, char **av, char **path);

#endif