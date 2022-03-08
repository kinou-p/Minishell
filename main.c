/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 17:28:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **path)
{
	char	*input;
	t_cmd	*cmd;

	printf("---MINISHELL  START---\n");
	while (1)
	{
		input = readline("$~ ");
		add_history(input);
		cmd = set_cmd(input, path);
		execute(cmd);
	}
	return (0);
}
