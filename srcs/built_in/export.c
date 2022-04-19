/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syd <syd@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:26:59 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/19 23:11:33 by syd              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_variable(char *variable)
{
	int	i;

	i = 0;
	if (!ft_isalpha(variable[i]) && variable[i] != '_')
		return (1);
	i++;
	while (variable[i] && variable[i] != '=')
	{
		if (!ft_isalnum(variable[i]) && variable[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	reatribute_variable(t_s_cmd *cmd, int index, char *dest, char *unset)
{
	free (cmd->big_cmd->env[index]);
	cmd->big_cmd->env[index] = dest;
	free(unset);
	return (check_return(cmd, 0));
}

int	ft_export_variable(t_s_cmd *cmd, char *variable)
{
	char	*dest;
	char	*unset;
	int		index;

	if (check_variable(variable) == 1)
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (check_return(cmd, 1));
	}
	dest = ft_strdup(variable);
	unset = ft_substr(dest, 0, find_len(dest, 0, '='));
	index = find_it(cmd->big_cmd->env, unset);
	if (index != -1)
		return (reatribute_variable(cmd, index, dest, unset));
	register_env(cmd, dest);
	if (dest)
		free(dest);
	if (unset)
		free(unset);
	return (check_return(cmd, 0));
}

int	ft_export(t_s_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!cmd->args[i])
		lone_export(cmd);
	else if (cmd->args[i])
	{
		while (cmd->args[i])
		{
			j = ft_export_variable(cmd, cmd->args[i]);
			i++;
		}
	}
	return (j);
}
