/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:58:40 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 18:02:15 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void	print_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			printf("%d -%s-\n", i, tab[i]);
			i++;
		}
		printf("end double\n");
	}
}

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
	return (0);
}

char	*get_command(char **exec, char **path)
{
	char	*swap;

	swap = 0;
	printf("in get command exec=\n");
	print_double(exec);
	if (exec[0][0] == '/' && !access(exec[0], F_OK))
	{
		printf("first\n");
		free_double(path);
		return (exec[0]);
	}
	else if (exec[0][0] == '/')
	{
		printf("BAD PATH FOR CMD\n");
		free_double(path);
		exit(1);
	}
	swap = does_access(path, exec);
	printf("swap bfore ret= %s\n", swap);
	return (swap);
}