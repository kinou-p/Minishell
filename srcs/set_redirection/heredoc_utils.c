/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:25:16 by apommier          #+#    #+#             */
/*   Updated: 2022/04/20 04:55:14 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		printf("Minishell: sigaction error2\n");
		return ;
	}
}

void	change_signal(void)
{
	struct sigaction	test;

	memset(&test, 0, sizeof(test));
	test.sa_handler = &sig_heredoc;
	test.sa_flags = 0;
	if (sigaction(SIGINT, &test, 0) == -1)
	{
		printf("Minishell: sigaction error\n");
		exit(1);
	}
}

int	free_wait_prompt(char *in, char**history)
{
	free(in);
	free_double(history);
	return (-1);
}

char	**fill_history(t_s_cmd *cmd, char *input, char *in, char **history)
{
	char	*del;
	char	*dup;

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
	return (history);
}
