/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:26:29 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/09 04:59:24 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_variable(t_s_cmd *cmd, int i)
{
	int	a;
	int	b;
	char	**tmp;

	a = 0;
	b = 0;
	tmp = malloc(sizeof(char *) * tab_len(cmd->big_cmd->env));
	if (!tmp)
		printf("no tmp\n");
		//ft_exit(cmd);
	while (cmd->big_cmd->env[a])
	{
		// if (a == i)
		// 	a++;
		// printf("%s\n", cmd->big_cmd->env[a]);
		if (a != i)
		{
			tmp[b] = ft_substr(cmd->big_cmd->env[a], 0, ft_strlen(cmd->big_cmd->env[a]));
			b++;
		}
		a++;
	}
	tmp[b] = NULL;
	free_double(cmd->big_cmd->env);
	a = 0;
	cmd->big_cmd->env = malloc(sizeof(char *) * (tab_len(tmp) + 1));
	if (!cmd->big_cmd->env)
		printf("no env\n");
		//ft_exit(cmd);
	while (tmp[a])
	{
		cmd->big_cmd->env[a] = ft_strdup(tmp[a]);
		// printf("%s\n", cmd->big_cmd->env[a]);
		a++;
	}
	cmd->big_cmd->env[a] = NULL;
	if (tmp)
		free_double(tmp);


}

void	find_variable(char *variable, t_s_cmd *cmd)
{
	// char	*str;
	int	i;
	int	j;

	i = find_it(cmd->big_cmd->env, variable);
	// str = ft_strjoin(variable, "=");
	j = 0;
	if (check_variable(variable) == 1)
	{
		ft_putstr_fd("Minishell: unset: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		// 2
		return ;
	}
	// while (str[j])
	// 	j++;
	// while (cmd->big_cmd->env[i] && !(ft_strncmp(cmd->big_cmd->env[i], str, j) == 0))
	// 	i++;
	if (i == tab_len(cmd->big_cmd->env))
		return ;
	unset_variable(cmd, i);
	// free(str);
}

void	ft_unset(t_s_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		find_variable(cmd->args[i], cmd);
		i++;
	}
}
