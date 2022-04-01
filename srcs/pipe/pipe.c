#include "../../includes/minishell.h"


void	close_pipe(t_cmd *cmd)
{
	int i;

	i = 0;
	close(0);
	while (cmd->s_cmds[i])// && !cmd->s_cmds[i]->last)
	{
		close(cmd->s_cmds[i]->last_pipe[0]);
		close(cmd->s_cmds[i]->last_pipe[1]);
		close(cmd->s_cmds[i]->fd[0]);
		close(cmd->s_cmds[i]->fd[1]);
		close(cmd->s_cmds[i]->pipe[0]);
		close(cmd->s_cmds[i]->pipe[1]);
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
		//dprintf(2, "exit_pid= %d\n", exit_pid);
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
	//dprintf(2, "return wait_exit\n");
	return (ret);
}



void    exec_cmd(t_cmd *cmd, char **env, int *fdpipe)
{
   // int    ret;

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
	//save in/out
	int fdpipe[2];
	//int ret;
	int fdout;
	int tmpin = dup(0);
	int tmpout= dup(1);
	int fdin;
	int i;

	i = 0;
	//close(0);
	//close(1);
	//if (cmd->current_s_cmd->infile)//set the initial input
	//	fdin = open(cmd->current_s_cmd->infile, O_APPEND);
		//fdin = open(cmd->current_s_cmd->infile, O_RDONLY);
	//else if (cmd->infile)
	//	fdin = open(cmd->infile, O_RDONLY);
	//else
	fdin=dup(tmpin);
	while(cmd->current_s_cmd)
	{
		if (i == cmd->nb_s_cmd - 1)
		{
			// Last simple command
			cmd->current_s_cmd->last = 1;
			if (cmd->current_s_cmd->outfile)
				fdout = open(cmd->current_s_cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0666);
			else if(cmd->outfile)
				fdout=open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
			else// Use default output
				fdout=dup(tmpout);
			cmd->current_s_cmd->fd[0] = fdin;
			cmd->current_s_cmd->fd[1] = fdout;
			exec_cmd(cmd, env, 0);
		}
		else 
		{
			cmd->current_s_cmd->last = 0;
			pipe(fdpipe);
			//cmd->current_s_cmd->pipe[0] = fdpipe[0];
			//cmd->current_s_cmd->pipe[1] = fdpipe[1];
			cmd->current_s_cmd->fd[0] = fdin;//entree current
			cmd->current_s_cmd->fd[1] = fdpipe[1];//sortie current
			cmd->current_s_cmd->pipe[0] = fdpipe[0];//entree prochaine cmd
			cmd->current_s_cmd->pipe[1] = fdpipe[1];//sortie current
			cmd->s_cmds[i + 1]->last_pipe[0] = fdpipe[0];
			cmd->s_cmds[i + 1]->last_pipe[1] = fdpipe[1];
			//fdout=fdpipe[1];
			fdin=fdpipe[0];
			exec_cmd(cmd, env, fdpipe);
			close(cmd->current_s_cmd->fd[0]);
		}
		close(cmd->current_s_cmd->pipe[1]);
		i++;
		cmd->current_s_cmd = cmd->s_cmds[i];
	} //while
	//restore in/out defaults
	close_pipe(cmd);
	wait_exit(cmd);
	//wait(0);
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
	
	// Wait for last command
	
} // execute