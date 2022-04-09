/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:30:26 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/09 04:55:48 by apommier         ###   ########.fr       */
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
	//printf("ici\n");
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

	i = ft_strlen(cmd->big_cmd->env[find_pwd(cmd)]);
	// printf("%s\n", cmd->args[6]);
	// while (cmd->big_cmd->env[find_pwd(cmd)][i])
	// 	i++;
	while (cmd->big_cmd->env[find_pwd(cmd)][i] != '/')
		i--;
	r = ft_substr(cmd->big_cmd->env[find_pwd(cmd)], 0, i);
	// printf ("-->%s\n", r);
	// free(cmd->big_cmd->env[find_pwd(cmd)]);
	if (r)
		cmd->big_cmd->env[find_pwd(cmd)] = ft_strdup(r);
	else
		cmd->big_cmd->env[find_pwd(cmd)] = ft_strdup("PWD=/");

	if (r)
		free(r);
}

void	add_one(t_s_cmd *cmd, char *str)
{
	char *r;

	r = ft_strjoin(cmd->big_cmd->env[find_pwd(cmd)], "/");
	r = ft_strjoin(r, str);
	//free(cmd->big_cmd->env[find_pwd(cmd)]);
	cmd->big_cmd->env[find_pwd(cmd)] = ft_strdup(r);
	free(r);
}

void	change_path(t_s_cmd *cmd)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_split(cmd->args[1], '/');
	while (cmd->big_cmd->env[i])
	{
		if (ft_strncmp(cmd->big_cmd->env[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	// printf("%d\n", i);
	/*if (cmd->big_cmd->env[i])
		free(cmd->big_cmd->env[i]);*/
	cmd->big_cmd->env[i] = ft_strjoin("OLD", cmd->big_cmd->env[find_pwd(cmd)]);
	i = 0;
	while (tab[i])
	{
		// printf("%d -> %s\n", tab_len(tab), tab[i]);
		// if (tab_len(tab) < 2)
		// 	break ;
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
			del_one(cmd);
		i--;
	}
	str = ft_substr(cmd->args[1], 2, ft_strlen(cmd->args[1]));
	cmd->args[1] = ft_strdup(str);
	free(str);
}

int	find_it(char **str, char *s)
{
	int i;

	i = 0;
	while (str[i] && ft_strncmp(str[i], s, ft_strlen(s)))
		i++;
	if (str[i] == NULL)
		return (0);
	return (i);
}

void	open_directory(t_s_cmd *cmd)
{
	char **str;
	int j;

	str = ft_split(cmd->big_cmd->env[find_pwd(cmd)], '/');
	// printf("jojo\n");
	// printf("%s\n", cmd->big_cmd->env[find_it(cmd->big_cmd->env, "HOME=")]);
	if (find_it(cmd->big_cmd->env, "HOME=") == 0)
	{
		//printf("%d\n", tab_len(cmd->args[1]));
		printf("bash: cd: HOME not set\n");
		return ;
	}
	j = tab_len(str);
	if (!cmd->args[1])
	{
		// reboot_pwd(cmd, j);
		// if (tab_len(str) > 3)
		// {
		// 	while (j-- > 3)
		// 		if (chdir("..") == 0)
		// 			del_one(cmd);
		// }
		// else
		// {
			char *p = ft_substr(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "HOME=")], 5, ft_strlen(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "HOME=")]));
            printf("%s\n", p);
			if (chdir(p) == 0)
			{
				cmd->big_cmd->env[find_it(cmd->big_cmd->env, "OLDPWD=")] = ft_strjoin("OLD", cmd->big_cmd->env[find_pwd(cmd)]);
				cmd->big_cmd->env[find_pwd(cmd)] = ft_strjoin("PWD=", p);
			}
			free(p);
			// printf("%s\n", p);
		// }
	}
	if (tab_len(cmd->args) == 2)
	{
		if (cmd->args[1][0] == '~')
			reboot_pwd(cmd, j);
		if (chdir(cmd->args[1]) == 0)
			change_path(cmd);
	}
	if (str)
		free_double(str);
}

void	ft_pwd(t_s_cmd *cmd)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (cmd->big_cmd->env[find_pwd(cmd)][j] != '=')
		j++;
	j += 1;
	while (cmd->big_cmd->env[find_pwd(cmd)][j])
	{
		write (1, &cmd->big_cmd->env[find_pwd(cmd)][j], 1);
		j++;
	}
	write(1, "\n", 1);
}