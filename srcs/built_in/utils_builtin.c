/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syd <syd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:04:12 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/20 00:13:17 by syd              ###   ########.fr       */
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

int	find_it(char **str, char *s)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	while (str[i] && (ft_strncmp(str[i], s, size)
			|| (!ft_strncmp(str[i], s, size)
				&& (str[i][size] != '=' && str[i][size] != 0))))
		i++;
	if (str[i] == NULL)
		return (-1);
	return (i);
}

int	cd_error(t_s_cmd *cmd, char *str, int i)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (check_return(cmd, i));
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

int	check_return(t_s_cmd *cmd, int var)
{
	if (cmd->child)
	{
		cmd->big_cmd->err_var = var;
		return (var);
	}
	else
	{
		close(cmd->big_cmd->tmpin);
		close(cmd->big_cmd->tmpout);
		free_cmd(cmd->big_cmd);
		exit(var);
	}
}
