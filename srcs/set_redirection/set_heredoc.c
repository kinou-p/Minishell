/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:46:01 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 19:36:08 by apommier         ###   ########.fr       */
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

int	wait_prompt(t_s_cmd *cmd, int index, int i, char *input)
{
	char				**history;
	char				*in;

	change_signal();
	in = ft_strjoin(cmd->infile, "\n");
	free(cmd->infile);
	cmd->infile = 0;
	history = 0;
	while (i == 0 || (input && ft_strlen(input) && ft_strcmp(input, in)))
	{
		i = 1;
		if (input)
			free(input);
		ft_putstr_fd("> ", 0);
		input = get_next_line(0);
		if (!input)
			return (free_wait_prompt(in, history));
		history = fill_history(cmd, input, in, history);
	}
	free(in);
	free(input);
	cmd->infile = set_heredoc(index, history);
	cmd->in_type = 0;
	return (1);
}
