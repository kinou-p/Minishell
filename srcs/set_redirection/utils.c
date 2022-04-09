/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:35:37 by apommier          #+#    #+#             */
/*   Updated: 2022/04/09 04:34:47 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	double_size(char **tab)
{
	int i;

	i = 0;
	if (tab == 0)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	free_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void	print_double_fd(char **tab, int fd)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			ft_putstr_fd(tab[i], fd);
			ft_putstr_fd("\n", fd);
			i++;
		}
	}
}