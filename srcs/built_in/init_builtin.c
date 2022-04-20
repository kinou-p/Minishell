/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:17:01 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/20 04:56:50 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_shlvl(char **env)
{
	int		i;
	int		index;
	char	*str;

	i = 0;
	index = find_it(env, "SHLVL");
	if (index != -1)
	{
		while (env[index][i] && env[index][i] != '=')
			i++;
		str = ft_substr(env[index], i + 1, ft_strlen(env[index]));
		i = ft_atoi(str);
		free (str);
		i += 1;
		str = ft_itoa(i);
		free (env[index]);
		env[index] = ft_strjoin("SHLVL=", str);
		free (str);
	}
}

void	register_env(t_s_cmd *cmd, char *variable)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	tmp = (char **)malloc(sizeof(char *) * (tab_len(cmd->big_cmd->env) + 2));
	if (!tmp)
		return ;
	while (cmd->big_cmd->env[i])
	{
		tmp[i] = ft_strdup(cmd->big_cmd->env[i]);
		i++;
	}
	tmp[i] = ft_strdup(variable);
	tmp[i + 1] = NULL;
	free_double(cmd->big_cmd->env);
	cmd->big_cmd->env = ft_dup_double(tmp);
	if (tmp)
		free_double(tmp);
}

void	ft_env(t_s_cmd *cmd, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	cmd->big_cmd->env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		cmd->big_cmd->env[i] = ft_strdup(env[i]);
		i++;
	}
	cmd->big_cmd->env[i] = NULL;
}

void	init_s_cmd(t_s_cmd *cmd, char **env)
{
	ft_env(cmd, env);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
