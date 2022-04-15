/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:23:32 by apommier          #+#    #+#             */
/*   Updated: 2022/04/15 13:02:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_s_cmd *cmd)
{
	int	i;

	i = -1;
	//printf("nb_args= %d\n", cmd->nb_args);
	if (cmd->nb_args > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		if (cmd->child)
			cmd->big_cmd->err_var = 1;
		else
			exit(1);
		return ;
	}
	else if (cmd->nb_args == 1)
		exit_shell(cmd->big_cmd, 0);
	while (cmd->args[1][++i])
	{
		if (!ft_isdigit(cmd->args[1][i]) && !(cmd->args[1][i] == '-' && ft_isdigit(cmd->args[1][i + 1])))
		{
			ft_putstr_fd("Minishell: exit: numeric argument required\n", 2);
			exit_shell(cmd->big_cmd, 2);
		}
	}
	exit_shell(cmd->big_cmd, ft_atoi(cmd->args[1]));
}