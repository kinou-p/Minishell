/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:30:26 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/11 17:54:03 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ls(char *input)
{
	int	i;

	DIR *dir;
	struct dirent *sd;

	i = ft_strlen("ls");
	while (input[i] && input[i] != ' ')
		i++;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("stop\n");
		return ;
	}
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

	if (find_it(cmd->big_cmd->env, "PWD"))
	{

	i = ft_strlen(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
	while (cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")][i] != '/')
		i--;
	r = ft_substr(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")], 0, i);
	if (r)
		cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")] = ft_strdup(r);
	else
		cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")] = ft_strdup("PWD=/");

	if (r)
		free(r);
	}
}

void	add_one(t_s_cmd *cmd, char *str)
{
	char *r;
	char *s;

	s = ft_strjoin(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")], "/");
	r = ft_strjoin(s, str);
	//free(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
	cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")] = ft_strdup(r);
	free(r);
	free(s);
}

void	change_path(t_s_cmd *cmd)
{
	char **tab;
	int i;

	tab = ft_split(cmd->args[1], '/');
	i = find_it(cmd->big_cmd->env, "OLDPWD");
	// while (cmd->big_cmd->env[i])
	// {
	// 	if (ft_strncmp(cmd->big_cmd->env[i], "OLDPWD=", 7) == 0)
	// 		break ;
	// 	i++;
	// }
	cmd->big_cmd->env[i] = ft_strjoin("OLD", cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "..") == 0)
			del_one(cmd);
		else
			add_one(cmd, tab[i]);
		i++;
	}
	if (tab)
		free_double(tab);
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

void	check_home(t_s_cmd *cmd, char *p)
{
	int home;
	int len_home;
	int old_pwd;
	int pwd;

	home = find_it(cmd->big_cmd->env, "HOME");
	len_home = ft_strlen(cmd->big_cmd->env[home]);
	old_pwd = find_it(cmd->big_cmd->env, "OLDPWD");
	pwd = find_it(cmd->big_cmd->env, "PWD");

	p = ft_substr(cmd->big_cmd->env[home], 5, ft_strlen(cmd->big_cmd->env[len_home]));
	if (chdir(p) == 0)
		if (find_it(cmd->big_cmd->env, "PWD") != -1)
		{
			cmd->big_cmd->env[old_pwd] = ft_strjoin("OLD", cmd->big_cmd->env[pwd]);
			cmd->big_cmd->env[pwd] = ft_strjoin("PWD=", p);
		}
	free(p);
}

int	open_directory(t_s_cmd *cmd)
{
	char *p;
	int j;

	p = NULL;
	if (find_it(cmd->big_cmd->env, "PWD") != -1)
		j = size_path(cmd->big_cmd->env);
	if (cmd->nb_args > 2)
	{
		// ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		// return ;
		return (cd_error(cmd, "Minishell: cd: too many arguments", 1));
	}
	if (!cmd->args[1])
	{
		if (find_it(cmd->big_cmd->env, "HOME") < 0)
		{
			// ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			// return ;
			return (cd_error(cmd, "Minishell: cd: HOME not set", 1));
		}
		check_home(cmd, p);
	}
	if (tab_len(cmd->args) == 2)
	{
		if (cmd->args[1][0] == '~')
			reboot_pwd(cmd, j);
		if (chdir(cmd->args[1]) == 0)
		{
			if (find_it(cmd->big_cmd->env, "PWD") != -1)
				change_path(cmd);
		}
		else
		{
			return (msg_error(cmd, "Minishell: cd: ", cmd->args[1], ": No such directory\n", 1));
			// ft_putstr_fd("Minishell: cd: ", 2);
			// ft_putstr_fd(cmd->args[1], 2);
			// ft_putstr_fd(": No such directory\n", 2);
			// return ;//(1);
		}
	}
	return (check_return(cmd, 0));
}

