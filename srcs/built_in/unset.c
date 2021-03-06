/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:26:29 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/23 13:09:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_variable(t_s_cmd *cmd, int i)
{
	int		a;
	int		b;
	char	**tmp;

	a = 0;
	b = 0;
	tmp = malloc(sizeof(char *) * tab_len(cmd->big_cmd->env));
	if (!tmp)
		return ;
	while (cmd->big_cmd->env[a])
	{
		if (a != i)
		{
			tmp[b] = ft_strdup(cmd->big_cmd->env[a]);
			b++;
		}
		a++;
	}
	tmp[b] = NULL;
	free_double(cmd->big_cmd->env);
	cmd->big_cmd->env = ft_dup_double(tmp);
	if (tmp)
		free_double(tmp);
}

int	find_variable(char *variable, t_s_cmd *cmd)
{
	int	i;

	i = find_it(cmd->big_cmd->env, variable);
	if (check_variable(variable) == 1)
	{
		ft_putstr_fd("Minishell: unset: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (check_return(cmd, 1));
	}
	if (i == tab_len(cmd->big_cmd->env))
		return (check_return(cmd, 2));
	if (find_it(cmd->big_cmd->env, variable) != -1)
	{
		unset_variable(cmd, i);
		return (check_return(cmd, 0));
	}
	else
		return (check_return(cmd, 1));
}

int	ft_unset(t_s_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd->args[i])
	{
		j = find_variable(cmd->args[i], cmd);
		i++;
	}
	return (j);
}
