/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:04:12 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/05 03:47:53 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_len(char *input, int i, char c)
{
	int	j;

	j = i;
	while (input[j] && input[j] != c)
		j++;
	return (j);
}


int    find_it(char **str, char *s)
{
	int i;

	i = 0;
	while (str[i] && (ft_strncmp(str[i], s, ft_strlen(s)) || (!ft_strncmp(str[i], s, ft_strlen(s)) && (str[i][ft_strlen(s)] != '=' && str[i][ft_strlen(s)] != 0))))
		i++;
	if (str[i] == NULL)
		return (-1);
	return (i);
}

int	 cd_error_simple(char *str, int i)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (i);
}

int msg_error(char *cmd, char *entry, char *error, int i)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(entry, 2);
	ft_putstr_fd(error, 2);
	return (i);
}

int	size_path(char **str)
{
	int		i;
	int		j;
	char	**s;

	i = find_it(str, "PWD");
	s = ft_split(str[i], '/');
	j = double_size(s);
	free_double(s);
	return (j);
}