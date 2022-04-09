/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:40 by apommier          #+#    #+#             */
/*   Updated: 2022/04/08 01:03:54 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



char	**get_path(char **env)
{
	int		i;
	char	**line;
	char	*swap;

	i = 0;
	line = 0;
	swap = 0;
	while (env[i++] && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			swap = ft_substr(env[i], 5, ft_strlen(env[i]));
			if (!swap)
				exit(1);
			line = ft_split(swap, ':');
			if (!line)
				exit(1);
			free(swap);
			return (line);
		}
		free(line);
	}
	return (0);
}


//verify access with cmd access
char	*does_access(char **path, char **exec)
{
	int		i;
	char	*cmd;
	char	*swap;

	swap = 0;
	cmd = 0;
	i = 0;
	if (exec[0][0] != '/')
		swap = ft_strjoin(path[i], "/");
	cmd = ft_strjoin(swap, exec[0]);
	free(swap);
	swap = cmd;
	while (access(swap, F_OK) && path[i++])
	{
		free(swap);
		swap = ft_strjoin(path[i], "/");
		cmd = swap;
		swap = ft_strjoin(swap, exec[0]);
		free(cmd);
	}
	if (path[i])
		return (swap);
	free(swap);
	return (0);
}

char	*get_command(char **exec, char **path)
{
	char	*swap;

	swap = 0;
	if ((exec[0][0] == '/' || exec[0][0] == '.') && !access(exec[0], F_OK))
	{
		//free_double(path);
		return (exec[0]);
	}
	else if (exec[0][0] == '/')
	{
		printf("BAD PATH FOR CMD\n");
		//free_double(path);
		return(0);
	}
	swap = does_access(path, exec);
	return (swap);
}