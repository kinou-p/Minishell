/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:19:42 by apommier          #+#    #+#             */
/*   Updated: 2022/04/23 13:07:57 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_s_cmd	*set_s_cmd(char *line, int index)
{
	t_s_cmd	*s_cmd;
	char	**split_line;

	s_cmd = malloc(sizeof(t_s_cmd));
	if (!s_cmd)
		return (0);
	s_cmd->fd[0] = -1;
	s_cmd->fd[1] = -1;
	s_cmd->cmd = 0;
	s_cmd->args = 0;
	s_cmd->infile = 0;
	s_cmd->outfile = 0;
	line = set_redirection(s_cmd, ft_strdup(line), index, 0);
	if (!line)
	{
		free(s_cmd);
		return (0);
	}
	split_line = ft_split_with_quote(line, ' ');
		s_cmd->nb_args = double_size(split_line);
		s_cmd->args = split_line;
	free(line);
	return (s_cmd);
}

t_cmd	*split_cmd(t_cmd *cmd, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		cmd->s_cmds[i] = set_s_cmd(cmds[i], i);
		if (!cmd->s_cmds[i])
		{
			free_cmd(cmd);
			return (0);
		}
		cmd->s_cmds[i]->big_cmd = cmd;
		i++;
	}
	cmd->s_cmds[i] = 0;
	return (cmd);
}

int	is_pipe_good(char *str)
{
	int		i;
	char	next;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			next = next_space(str, i + 1);
			if (!next || next == '|' || next == '<' || next == '>')
				return (0);
		}
		i++;
	}
	return (1);
}

t_cmd	*initialize_cmd(t_cmd *cmd, char **env, char **cmds, int nb)
{
	cmd->tmpin = -1;
	cmd->tmpout = -1;
	cmd->err_var = nb;
	cmd->path = get_path(env);
	cmd->env = ft_dup_double(env);
	cmd->nb_s_cmd = double_size(cmds);
	cmd = split_cmd(cmd, cmds);
	if (!cmd)
	{
		free_double(cmds);
		return (0);
	}
	parse_quote(cmd);
	free_double(cmds);
	if (cmd)
	{
		cmd->current_s_cmd = cmd->s_cmds[0];
		cmd->err_var = 0;
		return (cmd);
	}
	return (0);
}

t_cmd	*set_cmd(char *input, char **env, int nb)
{
	t_cmd	*cmd;
	char	**cmds;

	if (!is_quote_good(input) || !is_pipe_good(input))
	{
		error_parsing(0);
		return (0);
	}
	cmds = ft_split_with_quote(input, '|');
	if (!cmds)
		return (0);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->s_cmds = ft_calloc(sizeof(t_s_cmd), double_size(cmds) + 1);
	if (!cmd->s_cmds)
		return (0);
	return (initialize_cmd(cmd, env, cmds, nb));
}
