/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:23:32 by apommier          #+#    #+#             */
/*   Updated: 2022/04/20 17:48:23 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned long long    ft_atoi_long(const char *nptr)
{
    int                    i;
    unsigned long long    nbr;
    unsigned long long    minus;

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
	unsigned long long long_max;

	long_max = 9223372036854775807;
	printf("%s\n", nbr);
	if (ft_strlen(nbr) > 20)
		return (1);
	if (nbr[0] == '-')
	{
		printf("--->%lld\n", ft_atoi_long(nbr));
		if (ft_atoi_long(nbr + 1) > long_max + 1)
			return (1);
	}
	else if (ft_atoi_long(nbr) > long_max)
		return (1);
	printf("return 0\n");
	return (0);
}

void	exit_error(t_cmd *cmd)
{
	ft_putstr_fd("Minishell: exit: numeric argument required\n", 2);
	exit_shell(cmd, 2);
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
		if ((!ft_isdigit(cmd->args[1][i]) && !(cmd->args[1][i] == '-'
			&& ft_isdigit(cmd->args[1][i + 1]))))
			exit_error(cmd->big_cmd);
	}
	if (max_long(cmd->args[1]))
		exit_error(cmd->big_cmd);
	exit_shell(cmd->big_cmd, ft_atoi(cmd->args[1]));
}
