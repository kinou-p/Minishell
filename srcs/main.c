/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/03/10 11:07:08 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	red()
{
	printf("\033[1;31m");
}

void	normal()
{
	printf("\033[0m");
}

void	print_prompt(char **path)
{
	char	*input;
	t_cmd	*cmd;
	
	cmd = 0;
	while (1)
	{
		red();
		printf("~$");
		normal();
		input = readline(" ");
		if (!ft_strcmp("exit", input))
		{
			rl_clear_history();
			free(input);
			exit_shell(cmd);
		}
		if (ft_strlen(input) && next_space(input, 0))
		{
			add_history(input);
			cmd = set_cmd(input, path);
			free(input);
			if (cmd)
			{
				execute(cmd, path);
				free_cmd(cmd);
				cmd = 0;
			}
			//free_cmd(cmd);
			//cmd = 0;
		}
	}
}

void test(int num)
{
	num = 0;
	printf("CRTL-C ? try exit\n");
}

int	main(int ac, char **av, char **path)
{
	av = 0;
	if (ac > 1)
	{
		printf("too much arguments\n");
		return (0);
	}
	printf("---MINISHELL  START---\n"); 
	signal(SIGINT, test);
	print_prompt(path);
	return (0);
}