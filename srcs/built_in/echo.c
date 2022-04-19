/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syd <syd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:52:56 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/19 17:09:24 by syd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_print(t_s_cmd *d, int i)
{
	while (d->args[i])
	{
		printf("%s", d->args[i]);
		if (d->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	ft_echo(t_s_cmd *d)
{
	int		i;
	size_t	j;
	int		is_option;

	i = 1;
	is_option = 0;
	while (d->args[i] && d->args[i][0] == '-')
	{
		j = 1;
		while (d->args[i][j] && d->args[i][j] == 'n')
			j++;
		if (j == ft_strlen(d->args[i]))
			is_option = 1;
		else
			break ;
		i++;
	}
	if (d->args[i])
		echo_print(d, i);
	if (is_option == 0)
		printf("\n");
	return (check_return(d, 0));
}
