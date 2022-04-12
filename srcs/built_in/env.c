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

void	print_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->current_s_cmd->nb_args > 1)
	{
		ft_putstr_fd("Minishell: env: '", 2);
		ft_putstr_fd(cmd->current_s_cmd->args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		// return (127);
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
	// return (0);
}

void	ft_pwd(t_s_cmd *cmd)
{
	(void)cmd;
	int	i;
	char p[1024];
	char *str;

	i = 1;
	str = getcwd(p, sizeof(p));
	if (!str)
	{
		ft_putstr_fd("Minishell: pwd: Not found\n", 2);
		// return (1);
	}
	else
		ft_putendl_fd(p, 1);
	// return (0);
}