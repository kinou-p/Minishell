/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:19:42 by apommier          #+#    #+#             */
/*   Updated: 2022/04/03 18:19:55 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



t_s_cmd	*set_s_cmd(char *line, t_cmd *cmd, int index)
{
	t_s_cmd	*s_cmd;
	char	**split_line;
	int	i;

	i = 0;
	//line = ft_split(line, ' ');	
	s_cmd = malloc(sizeof(t_s_cmd));
	if (!s_cmd)
		return (0);
	s_cmd->infile = 0;
	s_cmd->outfile = 0;
	s_cmd->args = 0;
	//printf("before redirect\n");
	line = set_redirection(s_cmd, line, index);//SET REDIRECTION
	split_line = ft_split(line, ' ');
	s_cmd->cmd = get_command(split_line, cmd->path);
	if (!s_cmd->cmd)
	{
		free(line);
		free_double(split_line);
		free(s_cmd);
		return (0);
	}
	s_cmd->nb_args = double_size(split_line);
	//set_redirection(s_cmd);
	s_cmd->args = split_line;
	free(line);
	return (s_cmd);
}

t_cmd *split_cmd(t_cmd *cmd, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		cmd->s_cmds[i] = set_s_cmd(cmds[i], cmd, i);
		if (!cmd->s_cmds[i])
		{
			printf("invalid command\n");
			free_cmd(cmd);
			return (0);
		}
		i++;
	}
	cmd->s_cmds[i] = 0;
	return (cmd);
}

t_cmd	*set_cmd(char *input, char **env)
{
	t_cmd	*cmd;
	char	**cmds;

	cmds = ft_split(input, '|');
	if (!cmds)
		return (0);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->s_cmds = malloc(sizeof(t_s_cmd) * double_size(cmds) + 1);
	if (!cmd->s_cmds)
		return (0);
	cmd->s_cmds[double_size(cmds)] = 0;	
	cmd->path = get_path(env);
	cmd->outfile = 0;
	cmd->infile = 0;
	cmd->nb_s_cmd = double_size(cmds);
	cmd = split_cmd(cmd, cmds); //split each cmd into args in s_cmd
	free(cmds);
	if (cmd)
	{
		cmd->current_s_cmd = cmd->s_cmds[0];//set first s_cmd
		return (cmd);
	}
	return (0);
}