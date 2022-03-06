/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:00:41 by sadjigui          #+#    #+#             */
/*   Updated: 2022/03/06 15:31:18 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	red()
{
	printf("\033[1;31m");
}

void	normal()
{
	printf("\033[0m");
}

void	boot_shell(t_struct *data)
{
	char *input;
	while(1)
	{
		red();
		input = readline("Minishell> ");
		lexer(input, data);
		add_history(input);
		normal();
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_struct data;

	init_struct(&data, env);
	boot_shell(&data);
}
