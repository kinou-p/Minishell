/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:30:26 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/20 15:52:57 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_one(t_s_cmd *cmd)
{
	char	p[1024];
	char	*str;
	int		i;

	i = find_it(cmd->big_cmd->env, "PWD");
	str = getcwd(p, sizeof(p));
	free(cmd->big_cmd->env[i]);
	cmd->big_cmd->env[i] = ft_strjoin("PWD=", p);
}

void	change_path(t_s_cmd *cmd)
{
	int	old;
	int	pwd;

	if (find_it(cmd->big_cmd->env, "OLDPWD") != -1)
	{
		pwd = find_it(cmd->big_cmd->env, "PWD");
		old = find_it(cmd->big_cmd->env, "OLDPWD");
		free(cmd->big_cmd->env[old]);
		cmd->big_cmd->env[old] = ft_strjoin("OLD", cmd->big_cmd->env[pwd]);
	}
	add_one(cmd);
}

int	check_home(t_s_cmd *cmd, char *p, char **env)
{
	int	home;
	int	len_home;
	int	old_pwd;
	int	pwd;

	home = find_it(env, "HOME");
	len_home = ft_strlen(env[home]);
	old_pwd = find_it(env, "OLDPWD");
	pwd = find_it(env, "PWD");
	p = ft_substr(env[home], 5, ft_strlen(env[len_home]));
	if (chdir(p) == 0)
	{
		change_oldpwd(env, old_pwd, pwd, p);	
		free(p);
		return (check_return(cmd, 0));	
	}
	else
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(p, 2);
		ft_putstr_fd(": No such directory\n", 2);
		free(p);		
		return (check_return(cmd, 1));
	}		
}

int	check_dir(t_s_cmd *cmd)
{
	if (chdir(cmd->args[1]) == 0)
	{
		if (find_it(cmd->big_cmd->env, "PWD") != -1)
			change_path(cmd);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": No such directory\n", 2);
		return (check_return(cmd, 1));
	}
	return (check_return(cmd, 0));
}

int	open_directory(t_s_cmd *cmd)
{
	char	*p;
	int		j;
	int		i;

	p = NULL;
	i = 0;
	if (find_it(cmd->big_cmd->env, "PWD") != -1)
		j = size_path(cmd->big_cmd->env);
	if (cmd->nb_args > 2)
		return (cd_error(cmd, "Minishell: cd: too many arguments", 1));
	if (!cmd->args[1])
	{
		if (find_it(cmd->big_cmd->env, "HOME") < 0)
			return (cd_error(cmd, "Minishell: cd: HOME not set", 1));
		return(check_home(cmd, p, cmd->big_cmd->env));
	}
	else if (cmd->nb_args == 2)
		i = check_dir(cmd);
	return (check_return(cmd, i));
}
