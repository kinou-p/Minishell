/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:00:05 by sadjigui          #+#    #+#             */
/*   Updated: 2022/03/01 18:55:10 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	find_len(char *input, int i)
{
	int	j;

	j = i;
	while (input[j])
		j++;
	return (j);
}

void	ft_export(char *input, t_struct *data)
{
	(void)data;
	int	i;
	int j;
	char *variable;

	i = 6;
	j = find_len(input, i);
	variable = ft_substr(input, i, j);
	if (j == i)
		printf("check\n");
	else if (j > i)
		ft_export_variable(data, variable);
}

void	free_char_tab(char **libre)
{
	int	i;

	i = 0;
	while (libre[i])
	{
		free(libre[i]);
		i++;
	}
	free(libre);
}

void	ft_exit(t_struct *data)
{
	int	i;

	i = 0;
	while (data->envy[i])
	{
		free(data->envy[i]);
		i++;
	}
	free(data->envy);
	exit(0);
}
