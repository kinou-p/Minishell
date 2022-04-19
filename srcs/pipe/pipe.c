/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:51:31 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 18:12:19 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_cmd *cmd, char **env, int *fdpipe)
{
	cmd->current_s_cmd->child = fork();
	if (cmd->current_s_cmd->child == 0)
	{
		if (fdpipe)
			close(fdpipe[0]);
		dup2(cmd->current_s_cmd->fd[0], 0);
		dup2(cmd->current_s_cmd->fd[1], 1);
		close(cmd->current_s_cmd->fd[0]);
		close(cmd->current_s_cmd->fd[1]);
		if (is_builtin(cmd->current_s_cmd->cmd))
		{
			call_builtin(cmd);
			exit(0);
		}
		check_access(cmd);
		if (-1 == execve(cmd->current_s_cmd->cmd,
				cmd->current_s_cmd->args, env))
			ft_putstr_fd("Minishell: exec error\n", 2);
		exit(126);
	}
	else if (!cmd->current_s_cmd->cmd || access(cmd->current_s_cmd->cmd, F_OK))
		cmd->err_var = 127;
	else
		cmd->err_var = 131;
}

void	exec_last_cmd(t_cmd *cmd, int *fdin, int *fdout, int i)
{
	cmd->current_s_cmd->last = 1;
	if (cmd->current_s_cmd->outfile)
		*fdout = open(cmd->current_s_cmd->outfile,
				O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		*fdout = dup(cmd->tmpout);
	cmd->current_s_cmd->fd[0] = *fdin;
	cmd->current_s_cmd->fd[1] = *fdout;
	if (i == 0 && is_builtin(cmd->current_s_cmd->cmd))
		call_builtin(cmd);
	else
		exec_cmd(cmd, cmd->env, 0);
}

void	exec_not_last_cmd(t_cmd *cmd, int *fdpipe, int *fdin, int *fdout)
{
	cmd->current_s_cmd->last = 0;
	pipe(fdpipe);
	cmd->current_s_cmd->fd[0] = *fdin;
	if (cmd->current_s_cmd->outfile)
	{
		*fdout = open(cmd->current_s_cmd->outfile,
				O_RDWR | O_CREAT | O_APPEND, 0666);
		cmd->current_s_cmd->fd[1] = *fdout;
	}
	else
		cmd->current_s_cmd->fd[1] = fdpipe[1];
	*fdin = fdpipe[0];
	exec_cmd(cmd, cmd->env, fdpipe);
	close(cmd->current_s_cmd->fd[0]);
}

void	set_fdin_not_first(t_cmd *cmd, int *fdin)
{
	close(*fdin);
	*fdin = open(cmd->current_s_cmd->infile, O_RDWR);
	if (*fdin < 0)
		printf("Minishell: open : bad file descriptor\n");
}

void	execute(t_cmd *cmd, char **env)
{
	int	fdpipe[2];
	int	fdout;
	int	fdin;
	int	i;

	i = 0;
	fdpipe[1] = -1;
	cmd->tmpin = dup(0);
	cmd->tmpout = dup(1);
	set_fdin(cmd, &fdin);
	while (cmd->current_s_cmd)
	{	
		cmd->current_s_cmd->child = 1;
		fdout = -1;
		if (i > 0 && cmd->current_s_cmd->infile)
			set_fdin_not_first(cmd, &fdin);
		if (i == cmd->nb_s_cmd - 1)
			exec_last_cmd(cmd, &fdin, &fdout, i);
		else
			exec_not_last_cmd(cmd, fdpipe, &fdin, &fdout);
		if (fdpipe[1] != -1)
			close(fdpipe[1]);
		cmd->current_s_cmd = cmd->s_cmds[++i];
	}
	reset_fds(cmd);
}
