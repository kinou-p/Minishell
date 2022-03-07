/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:13:32 by apommier          #+#    #+#             */
/*   Updated: 2022/03/07 11:52:26 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd, char *infile, char *outfile)
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
	if (infile) 
		fdin = open(infile,O_READ); 
	else //Use default input	
		fdin=dup(tmpin);

	while( i < numsimplecommands) 
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == numsimplecommands - 1)
		{
			if(outfile)// Last simple command
				fdout=open(outfile,â€¦â€¦);
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

	if (!background) {
	// Wait for last command
	waitpid(ret, NULL);
	}

} // execute 

