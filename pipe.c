/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:13:32 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 14:53:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd)
{
	//save in/out 
	int ret;
	int fdout;
	int tmpin = dup(0);
	int tmpout= dup(1);
	int fdin;
	int fdpipe[2];
	int i;

	i = 0;
	//set the initial input 
	if (current_s_cmd->cmd->infile)
		fdin = open(current_s_cmd->cmd->infile, O_READ);
	else if (cmd->infile)
		fdin = open(cmd->infile,O_READ);
	else
		fdin=dup(tmpin);
	while( i < cmd->nb_s_cmd) 
	{
		if (i != 0 && current_s_cmd->cmd->infile)
			fdin = open(current_s_cmd->cmd->infile,O_READ);
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == cmd->nb_s_cmd - 1)
		{
			// Last simple command
			if (current_s_cmd->cmd->outfile)
				fdout = open(current_s_cmd->cmd->outfile, â€¦â€¦);
			else if(cmd->outfile)
				fdout=open(cmd->outfile, â€¦â€¦);
			else// Use default output
				fdout=dup(tmpout);
		}
		else 
		{
			// Not last 
			//simple command
			//create pipe
			//int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}// if/else

		// Redirect output
		dup2(fdout,1);
		close(fdout);
 
		// Create child process
		ret=fork(); 
		if(ret==0)
		{
			execvp(scmd[i].args[0], scmd[i].args);
			perror(â€œexecvpâ€);
			_exit(1);
		}
		i++;
	} //while
 
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);

	if (!background)
	{
		// Wait for last command
		waitpid(ret, NULL);
	}

} // execute 

int main(int argc, char **argv)
{
	execute(t_cmd *cmd, char *infile, char *outfile);
}