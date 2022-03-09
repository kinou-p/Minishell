/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:13:32 by apommier          #+#    #+#             */
/*   Updated: 2022/03/09 20:43:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_cmd *cmd, char **env)
{
	//save in/out 
	int ret;
	int fdout;
	int tmpin = dup(0);
	int tmpout= dup(1);
	int fdin;
	int i;

	i = 0;
	if (cmd->current_s_cmd->infile)//set the initial input
		fdin = open(cmd->current_s_cmd->infile, O_RDONLY);
	//else if (cmd->infile)
	//	fdin = open(cmd->infile, O_RDONLY);
	else
		fdin=dup(tmpin);
	while( i < cmd->nb_s_cmd) 
	{
		//if (i)
		//	cmd->current_s_cmd++;
		if (i != 0 && cmd->current_s_cmd->infile)
			fdin = open(cmd->current_s_cmd->infile, O_RDONLY);
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		fdin = -1;
		//setup output
		if (i == cmd->nb_s_cmd - 1)
		{
			// Last simple command
			if (cmd->current_s_cmd->outfile)
				fdout = open(cmd->current_s_cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
			else if(cmd->outfile)
				fdout=open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
			else// Use default output
			{
				fdout=dup(tmpout);
			}
		}
		else 
		{
			//not last 
			//simple command
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}
		// redirect output
		dup2(fdout, 1);
		close(fdout);
		// create child process
		
		ret=fork();
		if(ret==0)
		{
			execve(cmd->current_s_cmd->cmd, cmd->current_s_cmd->args, env);//cmd->path);
			//_exit(1);
		}
		i++;
		cmd->current_s_cmd = cmd->s_cmds[i];
	} //while
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
	
	// Wait for last command
	waitpid(ret, NULL, 0);
} // execute 
