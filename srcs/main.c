/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/04/01 17:30:02 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_prompt(char **path)
{
	char	*input;
	t_cmd	*cmd;
	int		i;
	int tmpout = dup(1);
	int tmpin = dup(0);
	
	
	input = 0;
	i = 0;
	cmd = 0;
	while (1)
	{
		i = 0;
		//ft_putstr_fd("\033[1;31m~$ \033[0m", 2);
		/*input = get_next_line(0);
		while (input[i] != '\n' && input[i])
			i++;
		if (input[i] == '\n')
			input[i] = 0;*/
		//input = ft_strjoin(readline("\033[1;31m~$ \033[0m"), 0);
		input = readline("\033[1;31m~$ \033[0m");
		//if (!ft_strlen(input))
		//	printf("\n");
		add_history(input);
		//l_replace_line(0, 1);
		//rl_replace_line("\n", 1);
		//_on_new_line();
		//rl_redisplay();
		
		if (!ft_strcmp("exit", input) && input)
		{
			dprintf(2, "exit\n");
			rl_clear_history();
			//free(input);
			exit_shell(cmd);
		}
		if (ft_strlen(input) && next_space(input, 0) && input)
		{
			//printf("hre\n");
			//add_history(input);
			cmd = set_cmd(input, path);
			//free(input);
			if (cmd)
			{
				execute(cmd, path);
				dup2(tmpout, 1);
				dup2(tmpin, 0);
				//waitpid(-1, 0, 0);
				//free_cmd(cmd);
				cmd = 0;
			}
			//free_cmd(cmd);
			//cmd = 0;
			//rl_replace_line("test", 0);
		}
		//else
		//	dprintf(2, "no exec\n");
		//rl_replace_line("\n", 1);
		free(input);
	}
}

void test(int num)
{
	num = 0;
	//ft_putstr_fd("\n\033[1;31m~$ \033[0m", 1);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//num = 0;
	//if (num)
	//	printf("num = %d\n", num);
	//ft_putstr_fd("\b\b  ", 2);
	
	//ft_putstr_fd("\n", 2);
	//ft_putstr_fd("\033[1;31m~$ \033[0m", 1);
	//red();
	//normal();
	//printf("CRTL-C ? try exit\n");
}

void	just_exit(int num)
{
	num = 0;
	printf("crtl d\n");
	exit(0);
}

int	main(int ac, char **av, char **path)
{
	av = 0;
	if (ac > 1)
	{
		printf("too much arguments\n");
		return (0);
	}
	//ft_putstr_fd("\033[1;31m~$ \033[0m", 1);
	printf("---MINISHELL  START---\n"); 
	signal(SIGINT, test);
	signal(SIGQUIT, just_exit);
	print_prompt(path);
	return (0);
}