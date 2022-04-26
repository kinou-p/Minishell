/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:33:30 by apommier          #+#    #+#             */
/*   Updated: 2022/04/23 13:18:23 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(t_cmd *cmd, int ret)
{
	ft_putstr_fd("exit\n", 1);
	close (0);
	close (1);
	if (!cmd)
		exit(ret);
	if (cmd->tmpin != -1)
		close(cmd->tmpin);
	if (cmd->tmpout != -1)
		close(cmd->tmpout);
	if (cmd->current_s_cmd->fd[0] != -1)
		close(cmd->current_s_cmd->fd[0]);
	if (cmd->current_s_cmd->fd[1] != -1)
		close(cmd->current_s_cmd->fd[1]);
	free_cmd(cmd);
	rl_clear_history();
	cmd = 0;
	exit(ret);
}

void	del_heredoc(void)
{
	long	i;
	char	*str;
	char	*nbr;

	i = 0;
	while (i < 2147483647)
	{
		nbr = ft_itoa(i);
		if (i == 0)
			str = ft_strdup(".heredoc");
		else
			str = ft_strjoin(".heredoc", nbr);
		free(nbr);
		if (access(str, F_OK) == 0)
			unlink(str);
		else
		{
			free(str);
			return ;
		}
		free(str);
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	del_heredoc();
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
