/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:46:01 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 14:51:11 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*set_heredoc(int index, char **in)
{
	char	*nbr_file;
	char	*file_name;
	int		fd;
	int		i;

	i = 0;
	if (index)
	{
		nbr_file = ft_itoa(index + 1);
		file_name = ft_strjoin(".heredoc", nbr_file);
	}
	else
		file_name = ft_strjoin(".heredoc", 0);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd > 0)
	{
		print_double_fd(in, fd);
		free_double(in);
	}
	close(fd);
	return (file_name);
}

void	sig_heredoc(int num)
{
	struct sigaction	base;

	(void)num;
	memset(&base, 0, sizeof(base));
	base.sa_handler = &crtl_c;
	base.sa_flags = 0;
	ft_putchar_fd('\n', 1);
	if (sigaction(SIGINT, &base, 0) == -1)
	{
		printf("sigaction error2\n");
		return ;
	}
}

int	wait_prompt(t_s_cmd *cmd, int index)
{
	char				*input;
	int					i;
	char				**history;
	char				*in;
	char				*dup;
	char				*del;
	struct sigaction	test;

	memset(&test, 0, sizeof(test));
	test.sa_handler = &sig_heredoc;
	test.sa_flags = 0;
	in = ft_strjoin(cmd->infile, "\n");
	free(cmd->infile);
	cmd->infile = 0;
	if (sigaction(SIGINT, &test, 0) == -1)
	{
		printf("sigaction error\n");
		exit(1);
	}
	history = 0;
	input = 0;
	i = 0;
	while (i == 0 || (input && ft_strlen(input) && ft_strcmp(input, in)))
	{
		i = 1;
		if (input)
			free(input);
		ft_putstr_fd("> ", 0);
		input = get_next_line(0);
		if (!input)
		{
			free(in);
			free_double(history);
			return (-1);
		}
		if (ft_strcmp(input, in))
		{
			dup = ft_strdup(input);
			dup[ft_strlen(input) - 1] = 0;
			del = dup;
			dup = set_var(cmd->big_cmd, dup);
			history = add_line(history, dup);
			if (dup != del)
				free(del);
			free(dup);
		}
	}
	free(in);
	free(input);
	cmd->infile = set_heredoc(index, history);
	cmd->in_type = 0;
	return (1);
}