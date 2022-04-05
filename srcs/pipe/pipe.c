/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:51:31 by apommier          #+#    #+#             */
/*   Updated: 2022/04/05 18:26:19 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	close_pipe(t_cmd *cmd)
{
	int i;

	i = 0;
	close(0);
	while (cmd->s_cmds[i])
	{
		close(cmd->s_cmds[i]->fd[0]);
		close(cmd->s_cmds[i]->fd[1]);
		i++;
	}
}

int	wait_exit(t_cmd *cmd)
{
	int i;
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
            if (exit_pid == cmd->s_cmds[i]->child)
            {
				close(cmd->s_cmds[i]->fd[0]);
				close(cmd->s_cmds[i]->fd[1]);
            }
			i++;
        }
    }
	return (ret);
}



void    exec_cmd(t_cmd *cmd, char **env, int *fdpipe)
{
	if (is_builtin(cmd->current_s_cmd->cmd))
	{
		call_builtin(cmd, env);
		return ;
	}
    cmd->current_s_cmd->child = fork();
    if (cmd->current_s_cmd->child == 0)
    {
		if (fdpipe)
			close(fdpipe[0]);
		dup2(cmd->current_s_cmd->fd[0], 0);
		dup2(cmd->current_s_cmd->fd[1], 1);
		close(cmd->current_s_cmd->fd[0]);
		close(cmd->current_s_cmd->fd[1]);
        if (-1 == execve(cmd->current_s_cmd->cmd, cmd->current_s_cmd->args, env))
			dprintf(2, "exec error\n");
        exit(0);
    }
}

void	execute(t_cmd *cmd, char **env)
{
	int fdpipe[2];
	int fdout;
	int tmpin;
	int tmpout;
	int fdin;
	int i;

	i = 0;
	tmpin = dup(0);
	tmpout= dup(1);
	if (cmd->current_s_cmd->infile)
	{
		fdin = open(cmd->current_s_cmd->infile, O_RDWR);
		if (fdin < 0)
			printf("open error\n");
	}
	else
		fdin=dup(tmpin);
	while(cmd->current_s_cmd)
	{
		fdout = 0;
		if (i > 0 && cmd->current_s_cmd->infile)
		{
			fdin = open(cmd->current_s_cmd->infile, O_RDWR);
			if (fdin < 0)
				printf("open error\n");
		}
		if (i == cmd->nb_s_cmd - 1)
		{
			cmd->current_s_cmd->last = 1;
			if (cmd->current_s_cmd->outfile)
				fdout = open(cmd->current_s_cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
			else
				fdout=dup(tmpout);
			cmd->current_s_cmd->fd[0] = fdin;
			cmd->current_s_cmd->fd[1] = fdout;
			exec_cmd(cmd, env, 0);
		}
		else 
		{
			cmd->current_s_cmd->last = 0;
			pipe(fdpipe);
			cmd->current_s_cmd->fd[0] = fdin;
			if (cmd->current_s_cmd->outfile)
			{
				fdout = open(cmd->current_s_cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
				cmd->current_s_cmd->fd[1] = fdout;
			}
			else
				cmd->current_s_cmd->fd[1] = fdpipe[1];
			fdin=fdpipe[0];
			exec_cmd(cmd, env, fdpipe);
			close(cmd->current_s_cmd->fd[0]);
		}
		close(fdpipe[1]);
		i++;
		cmd->current_s_cmd = cmd->s_cmds[i];
	}
	close_pipe(cmd);
	wait_exit(cmd);
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
}