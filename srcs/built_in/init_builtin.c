/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:17:01 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/05 17:16:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	join_variable(t_s_cmd *cmd, char **v_v, int size, char **tab)
// {
// 	char *str;
// 	char *tmp;
//
// 	while (tab[size])
// 	{
// 		cmd->env[size] = ft_strdup(tab[size]);
// 		// printf("tmp----%s\n", tmp[size]);
// 		// printf("envy---%s\n", cmd->env[size]);
// 		size++;
// 	}
// 	str = ft_strjoin(v_v[0], "=");
// 	tmp = ft_strdup(str);
// 	free(str);
// 	str = ft_strjoin(tmp,v_v[1]);
// 	cmd->env[size] = ft_strdup(str);
// 	printf("ici\n");
// 	free(str);
// 	free(tmp);
// 	cmd->env[size + 1] = NULL;
// }

void	register_env(t_s_cmd *cmd, char *variable)
{
	char	**tmp = NULL;
	int i;
	i = 0;

	// tmp = NULL;
	// printf("TABLEN %d", tab_len(cmd->env));
	tmp = (char **)malloc(sizeof(char *) * (tab_len(cmd->env) + 2));
	if(!tmp)
		printf("no tmp\n");
	while (cmd->env[i])
	{
		tmp[i] = ft_strdup(cmd->env[i]);
		// printf("ici\n");
		// printf("%s\n", "let me in");
		i++;
	}
	// printf("i: %d %s\n",i,tmp[i]);
	// printf("%s\n", "brrrrrrr");
	tmp[i] = ft_strdup(variable);
	tmp[i + 1] = NULL;
	// printf("debut %p\n", tmp[2]);
	// printf("1--------------------\n");
	free_double(cmd->env);
	// printf("1--------------------\n");
	cmd->env = (char **)malloc(sizeof(char *) * (tab_len(tmp) + 1));
	if (!cmd->env)
		printf("no env\n");
	i = 0;
	while (tmp[i])
	{
		cmd->env[i] = ft_strdup(tmp[i]);
		// if (tmp[size])
		// 	free(tmp[size]);
		// printf("tmp----%s\n", tmp[size]);
		// printf("envy---%s\n", cmd->env[size]);
		i++;
	}
	cmd->env[i] = NULL;
	// printf("2--------------------\n");
	if (tmp)
		free_double(tmp);
	// printf("2--------------------\n");
	// int i = 0;
	// while (tmp[i])
	// {
	// 	printf("nano");
	// 	free(tmp[i]);
	// 	i++;
	// }
	// if(tmp)
	// 	free(tmp);
	// join_variable(cmd, variable, size, tmp);
}

void	ft_env(t_s_cmd *cmd, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	cmd->env = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		cmd->env[i] = ft_strdup(env[i]);
		i++;
	}
	cmd->env[i] = NULL;
}

int		find_pwd(t_s_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		if (!ft_strncmp(cmd->env[i], "PWD=", 4))
			return (i);
		i++;
	}
	return (0);
	// printf("%s\n", cmd->env[i]);
}

void	init_s_cmd(t_s_cmd *cmd, char **env)
{
	ft_env(cmd, env);
}

int	tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
