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

	if (find_it(cmd->big_cmd->env, "PWD"))
	{

	i = ft_strlen(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
	// printf("%s\n", cmd->args[6]);
	// while (cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")][i])
	// 	i++;
	while (cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")][i] != '/')
		i--;
	r = ft_substr(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")], 0, i);
	// printf ("-->%s\n", r);
	// free(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
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

	r = ft_strjoin(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")], "/");
	r = ft_strjoin(r, str);
	//free(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
	cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")] = ft_strdup(r);
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
	cmd->big_cmd->env[i] = ft_strjoin("OLD", cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
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

int    find_it(char **str, char *s)
{
	int i;

	i = 0;
	while (str[i] && (ft_strncmp(str[i], s, ft_strlen(s)) || (!ft_strncmp(str[i], s, ft_strlen(s)) && (str[i][ft_strlen(s)] != '=' && str[i][ft_strlen(s)] != 0))))
		i++;
	if (str[i] == NULL)
		return (-1);
	return (i);
}

void	open_directory(t_s_cmd *cmd)
{
	char **str;
	int j;

	if (find_it(cmd->big_cmd->env, "PWD"))
	{
		str = ft_split(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")], '/');
		j = double_size(str);
		free_double(str);
	}
	if (cmd->nb_args > 2)
	{
		printf("Minishell: cd: too many arguments\n");
		cmd->big_cmd->err_var = 1;
		return ;
	}
	if (!cmd->args[1])
	{
		if (find_it(cmd->big_cmd->env, "HOME") < 0)
		{
			// printf("---->%s\n", cmd->big_cmd->env[find_it(cmd->big_cmd->env, "HOME")]);
			printf("Minishell: cd: HOME not set\n");
			cmd->big_cmd->err_var = 1;
			return ;
		}
			char *p = ft_substr(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "HOME")], 5, ft_strlen(cmd->big_cmd->env[find_it(cmd->big_cmd->env, "HOME")]));
            printf("%s\n", p);
			if (chdir(p) == 0)
				if (find_it(cmd->big_cmd->env, "PWD"))
				{
					cmd->big_cmd->env[find_it(cmd->big_cmd->env, "OLDPWD")] = ft_strjoin("OLD", cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")]);
					cmd->big_cmd->env[find_it(cmd->big_cmd->env, "PWD")] = ft_strjoin("PWD=", p);
				}
			free(p);
	}
	if (tab_len(cmd->args) == 2)
	{
		if (cmd->args[1][0] == '~')
			reboot_pwd(cmd, j);
		if (chdir(cmd->args[1]) == 0)
		{
			if (find_it(cmd->big_cmd->env, "PWD"))
				change_path(cmd);
		}
		else
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd(": No such directory\n", 2);
			cmd->big_cmd->err_var = 1;
		}
	}
}

void	ft_pwd(t_s_cmd *cmd)
{
	int	i;
	char p[1024];
	char *str;

	i = 1;
	str = getcwd(p, sizeof(p));
	if (!str)
	{
		cmd->big_cmd->err_var = 1;
		ft_putstr_fd("Minishell: pwd: Not found\n", 2);
	}
	else
		ft_putendl_fd(p, 1);

}