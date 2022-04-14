/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:52:56 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/09 04:55:48 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_s_cmd *d)
{
	int	i;
	size_t j;
	int	is_option;

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
		while (d->args[i])
		{
			printf("%s", d->args[i]);
			if (d->args[i + 1] != NULL)
				printf(" ");
			i++;
		}
	if (is_option == 0)
		printf("\n");
	return (check_return(d, 0));
}
