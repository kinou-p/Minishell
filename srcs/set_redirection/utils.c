/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:35:37 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 14:47:21 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cut_str(char *str, int start, int end)
{
	char	*swap;
	char	*del;

	swap = 0;
	del = str;
	if (str[end])
		swap = ft_strjoin(&str[end], 0);
	str[start] = 0;
	str = ft_strjoin(str, swap);
	free(del);
	free(swap);
	return (str);
}

char	next_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (str[i]);
}

int	double_size(char **tab)
{
	int	i;

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
