/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:23:32 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 13:17:35 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	max_long(char *nbr)
{
	printf("%s\n", nbr);
	if (ft_strlen(nbr) > 19)
		return (1);
	if (ft_atoi(nbr) > 9223372036854775800 && nbr[ft_strlen(nbr) - 1] > '7')
		return (1);
	if (ft_atoi(nbr) < -9223372036854775800 && nbr[ft_strlen(nbr) - 1] > '8')
		return (1);
	printf("return 0\n");
	return (0);
}

void	ft_exit(t_s_cmd *cmd)
{
	int	i;

	i = -1;
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
		if ((!ft_isdigit(cmd->args[1][i]) && !(cmd->args[1][i] == '-' && ft_isdigit(cmd->args[1][i + 1]))))
		{
			ft_putstr_fd("Minishell: exit: numeric argument required\n", 2);
			exit_shell(cmd->big_cmd, 2);
		}
	}
	if (max_long(cmd->args[1]))
	{
		ft_putstr_fd("Minishell: exit: numeric argument required\n", 2);
		exit_shell(cmd->big_cmd, 2);
	}
	exit_shell(cmd->big_cmd, ft_atoi(cmd->args[1]));
}
