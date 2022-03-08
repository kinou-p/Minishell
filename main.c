/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 15:20:48 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **path)
{
	char	*input;

	printf("---MINISHELL  START---\n");
	
	execute(t_cmd *cmd, *infile, *outfile);
	while (1)
	{
		input = readline("$~ ");
		add_history(input);
		set_cmd(input);
	}
	return (0);
}
