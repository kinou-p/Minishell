/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/04/16 02:50:22 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void crtl_c(int num)
{
	num = 0;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//ft_putstr_fd("test\n", 0);
}

void	sig_quit(int num)
{
	num = 0;
	ft_putstr_fd("\b \b\b \b", 1);
	//printf("quit num= %d\n", num);
	//exit(0);
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
        new_tab[i] = ft_strjoin(env[i], 0);
        i++;
    }
    new_tab[i] = NULL;
	return (new_tab);
}

void	print_prompt(char **path)
{
	char	*input;
	t_cmd	*cmd;
	int		err_var;	
	
	input = 0;
	err_var = 0;
	cmd = 0;
	while (1)
	{
		input = readline("\033[1;31m~$ \033[0m");
		if (!input)
			exit_shell(cmd, 0);
		add_history(input);	
		/*if (!ft_strcmp("exit", input) && input)
		{
			free(input);
			exit_shell(cmd);
		}*/
		if (ft_strlen(input) && next_space(input, 0) && input)
		{
			cmd = set_cmd(input, path, err_var);
			if (cmd)
			{
				//cmd->err_var = 0;
				execute(cmd, path);
				err_var = cmd->err_var;
				path = ft_dup_double(cmd->env);
				free_cmd(cmd);
				cmd = 0;
			}
			else
				ft_putstr_fd("Minishell: error while parsing command\n", 2);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **path)
{
	char **env;

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
	print_prompt(env);
	return (0);
}