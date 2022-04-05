/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:26:29 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/05 03:54:57 by apommier         ###   ########.fr       */
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
	tmp = malloc(sizeof(char *) * tab_len(cmd->env));
	if (!tmp)
		printf("no tmp\n");
		//ft_exit(cmd);
	while (cmd->env[a])
	{
		// if (a == i)
		// 	a++;
		printf("%s\n", cmd->env[a]);
		if (a != i)
		{
			tmp[b] = ft_substr(cmd->env[a], 0, ft_strlen(cmd->env[a]));
			b++;
		}
		a++;
	}
	tmp[b] = NULL;
	free_double(cmd->env);
	a = 0;
	cmd->env = malloc(sizeof(char *) * (tab_len(tmp) + 1));
	if (!cmd->env)
		printf("no env\n");
		//ft_exit(cmd);
	while (tmp[a])
	{
		cmd->env[a] = ft_strdup(tmp[a]);
		// printf("%s\n", cmd->env[a]);
		a++;
	}
	cmd->env[a] = NULL;
	if (tmp)
		free_double(tmp);
	printf("2-------------\n");

}

void	find_variable(char *variable, t_s_cmd *cmd)
{
	char	*str;
	int	i;
	int	j;

	i = 0;
	str = ft_strjoin(variable, "=");
	j = 0;
	// printf("variable == %s\n", variable);
	while (str[j])
		j++;
	while (cmd->env[i] && !(ft_strncmp(cmd->env[i], str, j) == 0))
		i++;
	if (i == tab_len(cmd->env))
		return ;
	unset_variable(cmd, i);
	free(str);
	printf("%s\n", "3----------------");
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
