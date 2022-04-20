/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:36:53 by apommier          #+#    #+#             */
/*   Updated: 2022/04/20 04:50:19 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_exit(t_cmd *cmd)
{
	int	i;
	int	ret;
	int	exit_pid;
	int	status;

	i = 0;
	ret = 0;
	exit_pid = 1;
	while (exit_pid > 0)
	{
		i = 0;
		exit_pid = wait(&status);
		while (exit_pid != -1 && cmd->s_cmds[i])
		{
			exit_child(cmd, exit_pid, status, i);
			i++;
		}
	}
	return (ret);
}

void	exit_child(t_cmd *cmd, int exit_pid, int status, int i)
{
	if (exit_pid == cmd->s_cmds[i]->child)
	{
		close(cmd->s_cmds[i]->fd[0]);
		close(cmd->s_cmds[i]->fd[1]);
		if (WIFEXITED(status))
			cmd->err_var = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != 13)
				cmd->err_var = WTERMSIG(status);
			ft_putstr_fd("\b\b\b\b\b", 1);
			if (WTERMSIG(status) == 3)
				ft_putstr_fd("^\\Quit\n", 1);
		}
	}
}

void	check_access(t_cmd *cmd)
{
	if (!cmd->current_s_cmd->cmd || access(cmd->current_s_cmd->cmd, F_OK))
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		if (cmd->current_s_cmd->cmd)
			ft_putstr_fd(cmd->current_s_cmd->cmd, 2);
		ft_putstr_fd("\n", 2);
		close(0);
		close(1);
		close(cmd->tmpin);
		close(cmd->tmpout);
		free_cmd(cmd);
		exit(127);
	}
}

void	close_pipe(t_cmd *cmd)
{
	int	i;

	i = 0;
	close(0);
	while (cmd->s_cmds[i])
	{
		close(cmd->s_cmds[i]->fd[0]);
		close(cmd->s_cmds[i]->fd[1]);
		i++;
	}
}
