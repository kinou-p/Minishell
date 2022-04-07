/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/04/07 19:29:27 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void crtl_c(int num)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_quit(int num)
{
	ft_putstr_fd("\b \b\b \b", 1);
	//printf("quit num= %d\n", num);
	//exit(0);
}

void	print_prompt(char **path)
{
	char	*input;
	t_cmd	*cmd;
	int		i;
	
	input = 0;
	i = 0;
	cmd = 0;
	while (1)
	{
		i = 0;
		input = readline("\033[1;31m~$ \033[0m");
		if (!input)
			exit_shell(cmd);
		add_history(input);	
		if (!ft_strcmp("exit", input) && input)
		{
			rl_clear_history();
			exit_shell(cmd);
		}
		if (ft_strlen(input) && next_space(input, 0) && input)
		{
			cmd = set_cmd(input, path);
			if (cmd)
			{
				cmd->err_var = 0;
				execute(cmd, path);
				cmd = 0;
			}
		}
		free(input);
	}
}

char	**ft_dup_double(char **env)
{
	char	**new_tab;
    int		i;

    i = 0;
    while (env[i])
        i++;
    new_tab = ft_calloc(sizeof(char *), i + 1);
    i = 0;
    while (env[i])
    {
        new_tab[i] = ft_strdup(env[i]);
        i++;
    }
    new_tab[i] = NULL;
	return (new_tab);
}

int	main(int ac, char **av, char **path)
{
	char **env;

	env = ft_dup_double(path);
	av = 0;
	if (ac != 1)
	{
		printf("too much arguments\n");
		return (0);
	}
	printf("---MINISHELL  START---\n"); 
	signal(SIGINT, crtl_c);
	signal(SIGQUIT, sig_quit);
	print_prompt(env);
	return (0);
}