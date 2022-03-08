/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 20:22:56 by apommier         ###   ########.fr       */
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

int	main(int ac, char **av, char **path)
{
	char	*input;
	t_cmd	*cmd;

	printf("---MINISHELL  START---\n");
	while (1)
	{
		red();
		input = readline("$~ ");
		add_history(input);
		cmd = set_cmd(input, path);
		normal();
		execute(cmd);
	}
	return (0);
}
