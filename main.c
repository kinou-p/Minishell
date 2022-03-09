/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/03/09 11:37:23 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	
	while (1)
	{
		red();
		printf("~$");
		normal();
		input = readline(" ");
		if (ft_strlen(input))
		{
		add_history(input);
		cmd = set_cmd(input, path);
		if (cmd)
			execute(cmd, path);
		}
	}
}

int	main(int ac, char **av, char **path)
{
	printf("---MINISHELL  START---\n");
	print_prompt(path);
	return (0);
}
