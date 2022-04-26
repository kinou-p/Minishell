/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/04/23 13:16:15 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_dup_double(char **env)
{
	char	**new_tab;
	int		i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	new_tab = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		new_tab[i] = ft_strjoin(env[i], 0);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

char	**read_line(char **path, char *input, t_cmd *cmd, int *err_var)
{
	(void)*err_var;
	input = readline("\033[1;31m~$ \033[0m");
	if (!input)
	{
		free_double(path);
		exit_shell(cmd, 0);
	}
	add_history(input);
	if (ft_strlen(input) && next_space(input, 0) && input && path)
	{
		cmd = set_cmd(input, path, g_var);
		if (cmd)
		{
			free_double(path);
			execute(cmd);
			g_var = cmd->err_var;
			path = ft_dup_double(cmd->env);
			free_cmd(cmd);
			cmd = 0;
		}
	}
	free(input);
	return (path);
}

void	print_prompt(char **path)
{
	int	err_var;

	err_var = 0;
	while (1)
		path = read_line(path, 0, 0, &err_var);
}

int	main(int ac, char **av, char **path)
{
	char	**env;

	(void)av;
	if (!isatty(0))
	{
		printf("Not today\n");
		return (0);
	}
	env = ft_dup_double(path);
	av = 0;
	if (ac != 1)
	{
		ft_putstr_fd("Error: too much arguments\n", 2);
		return (0);
	}
	printf("---MINISHELL  START---\n");
	signal(SIGINT, crtl_c);
	signal(SIGQUIT, sig_quit);
	if (env)
		ft_shlvl(env);
	print_prompt(env);
	return (0);
}
