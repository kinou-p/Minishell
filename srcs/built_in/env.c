/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:09:47 by apommier          #+#    #+#             */
/*   Updated: 2022/04/09 21:23:45 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->current_s_cmd->nb_args > 1)
	{
		ft_putstr_fd("Minishell: env: too many arguments\n", 2);
		return (check_return(cmd->current_s_cmd, 127));
	}
	else if (cmd->env)
	{
		while (cmd->env[i])
		{
			if (ft_strchr(cmd->env[i], '='))
				ft_putendl_fd(cmd->env[i], 1);
			i++;
		}
	}
	return (check_return(cmd->current_s_cmd, 0));
}

int	ft_pwd(t_s_cmd *cmd)
{
	char p[1024];
	char *str;

	str = getcwd(p, sizeof(p));
	if (!str)
	{
		ft_putstr_fd("Minishell: pwd: Not found\n", 2);
		return (check_return(cmd, 1));
	}
	else
		ft_putendl_fd(p, 1);
	return (check_return(cmd, 0));
}