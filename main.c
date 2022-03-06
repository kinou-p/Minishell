/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/03/06 17:41:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	color()
{
	printf("\033[0m");
}

int	main(int ac, char **av, char **path)
{
	char	*input;

	printf("---MINISHELL  START---\n");
	while (1)
	{
		color();
		input = readline("$~ ");
		add_history(input);
	}
	return (0);
}
