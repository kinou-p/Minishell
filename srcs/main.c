/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:27:11 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 08:23:56 by apommier         ###   ########.fr       */
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
	(void)num;
	ft_putstr_fd("\b \b\b \b", 1);
	//printf("quit num= %d\n", num);
	//exit(0);
}

void	sig_quit2(int num)
{
	num = 0;
	//ft_putchar_fd(127, 1);
	//ft_putchar_fd(127, 1);
	ft_putstr_fd("\b \b\b \b", 1);
	ft_putstr_fd("sigquit2\n", 1);
	//printf("sig_quit2\n");
	//exit(0);
}

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

void	print_prompt(char **path)
{
	char	*input;
	t_cmd	*cmd;
	//int		tmpin = dup(0);
	//int		tmpout = dup(1);
	int		err_var;
	struct	sigaction test;
	
	memset(&test, 0, sizeof(test));
	test.sa_handler = &sig_quit;
	test.sa_flags = 0;
	input = 0;
	err_var = 0;
	cmd = 0;
	if (sigaction(SIGQUIT, &test, 0) == -1)
	{
		printf("Minishell: sigaction error\n");
		exit(1);
	}
	/*else
		printf("sigaction good\n");*/
	while (1)
	{
		input = readline("\033[1;31m~$ \033[0m");
		if (!input)
		{
			free_double(path);
			exit_shell(cmd, 0);
		}
		add_history(input);
		if (ft_strlen(input) && next_space(input, 0) && input && path)
		{
			cmd = set_cmd(input, path, err_var);
			//path = ft_dup_double(path);
			
			if (cmd)
			{
				free_double(path);
				//cmd->err_var = 0;
				execute(cmd, cmd->env);
				err_var = cmd->err_var;
				
				path = ft_dup_double(cmd->env);
				free_cmd(cmd);
				cmd = 0;
			}
			/*else
			{
				close(0);
				close(1);
				dup2(tmpin, 0);
				dup2(tmpout, 1);
				ft_putstr_fd("Minishell: error while parsing command\n", 2);
			}*/
		}
		free(input);
	}
}

int	main(int ac, char **av, char **path)
{
	char **env;
	
	if (!isatty(0))
	{
		printf("Not today\n");
		return (0);
	}
	//print_double_fd(path, 1);
	env = ft_dup_double(path);
	av = 0;
	if (ac != 1)
	{
		ft_putstr_fd("Error: too much arguments\n", 2);
		return (0);
	}
	printf("---MINISHELL  START---\n");
	signal(SIGINT, crtl_c);
	//signal(SIGQUIT, sig_quit);
	if (env)
		ft_shlvl(env);
	print_prompt(env);
	return (0);
}