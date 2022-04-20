/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:53:35 by apommier          #+#    #+#             */
/*   Updated: 2022/04/20 18:14:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned long long	ft_atoi_long(const char *nptr)
{
	int					i;
	unsigned long long	nbr;
	unsigned long long	minus;

	minus = 1;
	nbr = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		minus = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (minus * nbr);
}

int	max_long(char *nbr)
{
	unsigned long long	long_max;

	long_max = 9223372036854775807;
	if (ft_strlen(nbr) > 20)
		return (1);
	if (nbr[0] == '-')
	{
		if (ft_atoi_long(nbr + 1) > long_max + 1)
			return (1);
	}
	else if (ft_atoi_long(nbr) > long_max)
		return (1);
	return (0);
}

void	exit_error(t_cmd *cmd)
{
	ft_putstr_fd("Minishell: exit: numeric argument required\n", 2);
	exit_shell(cmd, 2);
}

int	check_exit_args(t_s_cmd *cmd)
{
	if (cmd->nb_args > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		if (cmd->child)
			cmd->big_cmd->err_var = 1;
		else
			exit(1);
		return (0);
	}
	return (1);
}

void	ft_exit(t_s_cmd *cmd)
{
	int	i;

	i = 0;
	if (!check_exit_args(cmd))
		return ;
	else if (cmd->nb_args == 1)
		exit_shell(cmd->big_cmd, 0);
	while (cmd->args[1][i] == ' ')
		i++;
	if (cmd->args[1][i] == '-')
		i++;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i++]))
			exit_error(cmd->big_cmd);
	}
	if (max_long(cmd->args[1]))
		exit_error(cmd->big_cmd);
	exit_shell(cmd->big_cmd, ft_atoi(cmd->args[1]));
}
