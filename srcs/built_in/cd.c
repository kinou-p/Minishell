/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:30:26 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/05 18:30:30 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ls(char *input)
{
	int	i;

	DIR *dir;
	struct dirent *sd;

	i = ft_strlen("ls");
	// if (input[i] == ' ')
	// {
	printf("ici\n");
		while (input[i] && input[i] != ' ')
			i++;
	// }
	// printf("[%c]\n", input[i]);
	// printf("[%c]\n", input[i+1]);

	dir = opendir(".");
	if (dir == NULL)
	{
		printf("stop\n");
		return ;
	}
	// printf("dir --> %s\n", dir[0]);
	while ((sd=readdir(dir)) != NULL)
	{
		printf(" >> %s\n", sd->d_name);
	}
	closedir(dir);
}

void	del_one(t_s_cmd *cmd)
{
	int	i;
	char *r;

	i = ft_strlen(cmd->env[find_pwd(cmd)]);
	// printf("%s\n", cmd->args[6]);
	// while (cmd->env[find_pwd(cmd)][i])
	// 	i++;
	while (cmd->env[find_pwd(cmd)][i] != '/')
		i--;
	r = ft_substr(cmd->env[find_pwd(cmd)], 0, i);
	printf("-------------\n");
	printf("%s\n", cmd->env[find_pwd(cmd)]);
	printf("%d\n", find_pwd(cmd));
	// free(cmd->env[find_pwd(cmd)]);
	cmd->env[find_pwd(cmd)] = r;
	// cmd->env[find_pwd(cmd)] = ft_strdup(r);
	free(r);
}

void	add_one(t_s_cmd *cmd, char *str)
{
	char *r;

	r = ft_strjoin(cmd->env[find_pwd(cmd)], "/");
	r = ft_strjoin(r, str);
	// free(cmd->env[find_pwd(cmd)]);
	cmd->env[find_pwd(cmd)] = ft_strdup(r);
	free(r);
}

int	find_it(t_s_cmd *cmd, char *str)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], str, ft_strlen(str)) == 0)
		{
			printf("--->%s\n", cmd->env[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	change_path(t_s_cmd *cmd)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_split(cmd->args[1], '/');
	// while (cmd->env[i])
	// {
	// 	if (ft_strncmp(cmd->env[i], "OLDPWD=", 7) == 0)
	// 	{
	// 		printf("--->%s\n", cmd->env[i]);
	// 		break ;
	// 	}
	// 	i++;
	// }
	/*if (cmd->env[i])
		free(cmd->env[i]);*/
	if (find_it(cmd, "OLDPWD") == 1)
		cmd->env[i] = ft_strjoin("OLD", cmd->env[find_pwd(cmd)]);
	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "..") == 0)
			del_one(cmd);
		else
			add_one(cmd, tab[i]);
		i++;
	}
}

void	reboot_pwd(t_s_cmd *cmd, int i)
{
	char	*str;

	while (i > 3)
	{
		if (chdir("..") == 0)
		{
			del_one(cmd);
		}
		i--;
	}
	str = ft_substr(cmd->args[1], 2, ft_strlen(cmd->args[1]));
	cmd->args[1] = ft_strdup(str);
	free(str);
}

void	open_directory(t_s_cmd *cmd)
{
	char **str;
	int j;

	str = ft_split(cmd->env[find_pwd(cmd)], '/');
	j = tab_len(str);
	if (!cmd->args[1])
	{
		reboot_pwd(cmd, j);
		// while (j-- > 3)
		// 	if (chdir("..") == 0)
		// 		del_one(cmd);
	}
	if (tab_len(cmd->args) == 2)
	{
		if (cmd->args[1][0] == '~')
			reboot_pwd(cmd, j);
		if (chdir(cmd->args[1]) == 0)
			change_path(cmd);
	}
}

void	ft_pwd(t_s_cmd *cmd)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (cmd->env[find_pwd(cmd)][j] != '=')
		j++;
	j += 1;
	while (cmd->env[find_pwd(cmd)][j])
	{
		write (1, &cmd->env[find_pwd(cmd)][j], 1);
		j++;
	}
	write(1, "\n", 1);
}
