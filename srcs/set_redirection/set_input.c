/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:44:22 by apommier          #+#    #+#             */
/*   Updated: 2022/04/22 11:43:15 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_access_input(t_s_cmd *cmd)
{
	if (access(cmd->infile, R_OK))
	{
		g_var = 1;
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		if (access(cmd->infile, F_OK))
			ft_putstr_fd(": no such file\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		free(cmd->infile);
		return (0);
	}
	return (1);
}

char	*set_input(char *line, t_s_cmd *cmd, int index)
{
	int	i;
	int	word_index;

	word_index = 0;
	i = index + 1;
	if (line[i] == '<')
		i++;
	word_index = i;
	while (line[i] == ' ' && line[i])
		i++;
	while ((line[i] != ' ' && line[i] != '<' && line[i] != '>') && line[i])
		i++;
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = get_word(line, index);
	cmd->infile = set_var(cmd->big_cmd, cmd->infile);
	if (cmd->in_type == 0 && !check_access_input(cmd))
	{
		free(line);
		return (0);
	}
	line = cut_str(line, index, i);
	return (line);
}

char	*ft_input(char *line, t_s_cmd *cmd, int index)
{
	int		i;
	char	next;

	i = index;
	next = next_space(line, i + 1);
	if (line[i + 1] == '<')
	{
		cmd->in_type = 1;
		next = next_space(line, i + 2);
	}
	else
		cmd->in_type = 0;
	if (next == '<' || next == '>' || !next)
		return (error_parsing(line));
	line = set_input(line, cmd, i);
	if (!line)
		return (0);
	return (line);
}
