/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:33:30 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 12:01:16 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exit_shell(t_cmd *cmd, int ret)
{
	int i;
	
	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (!cmd)
		exit(ret);
	if (cmd->tmpin != -1)
	{
		dup2(cmd->tmpin, 0);
		close(cmd->tmpin);
	}
	if (cmd->tmpout != -1)
	{
		dup2(cmd->tmpout, 1);
		close(cmd->tmpout);
	}
	if (cmd->current_s_cmd->fd[0] != -1)
		close(cmd->current_s_cmd->fd[0]);
	if (cmd->current_s_cmd->fd[1] != -1)
		close(cmd->current_s_cmd->fd[1]);
	free_cmd(cmd);
	clear_history();
	cmd = 0;
	exit(ret);
}

void free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->s_cmds && cmd->s_cmds[i])
	{
		free_double(cmd->s_cmds[i]->args);
		if (cmd->s_cmds[i]->cmd)
			free(cmd->s_cmds[i]->cmd);
		if (cmd->s_cmds[i]->infile)
			free(cmd->s_cmds[i]->infile);
		if (cmd->s_cmds[i]->outfile)
			free(cmd->s_cmds[i]->outfile);
		free(cmd->s_cmds[i]);
		i++;
	}
	free_double(cmd->env);
	free_double(cmd->path);
	free(cmd->s_cmds);
	free(cmd);
}