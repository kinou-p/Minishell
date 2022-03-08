/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:13:32 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 17:16:44 by apommier         ###   ########.fr       */
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
	printf("in execute\n");
	//set the initial input 
	if (cmd->current_s_cmd->infile)
	{
		fdin = open(cmd->current_s_cmd->infile, O_RDONLY);
		printf("good chosse -redirect infile- fdin= %d\n", fdin);
	}
	else if (cmd->infile)
	{
		fdin = open(cmd->infile, O_RDONLY);
		printf("good chosse -infile- fdin= %d\n", fdin);
	}
	else
	{
		fdin=dup(tmpin);
		printf("good chosse -standar in- fdin= %d\n", fdin);
	}
	while( i < cmd->nb_s_cmd) 
	{
		printf("enter while\n");
		if (i != 0 && cmd->current_s_cmd->infile)
			fdin = open(cmd->current_s_cmd->infile, O_RDONLY);
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == cmd->nb_s_cmd - 1)
		{
			printf("if last cmd\n");
			// Last simple command
			if (cmd->current_s_cmd->outfile)
				fdout = open(cmd->current_s_cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
			else if(cmd->outfile)
				fdout=open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
			else// Use default output
				fdout=dup(tmpout);
		}
		else 
		{
			//not last 
			//simple command
			//create pipe
			//int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}
		printf("select if last or not done \n");
		// Redirect output
		dup2(fdout,1);
		close(fdout);
 
		// Create child process
		ret=fork();
		int return_exec;
		if(ret==0)
		{
			return_exec = execvp(cmd->current_s_cmd->cmd, cmd->current_s_cmd->args);
			printf("exec done ret exec= %d\n", return_exec);
			_exit(1);
		}
		i++;
		printf("good i = %d\n", i);
	} //while
	printf("quit while\n");
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
	
	// Wait for last command
	waitpid(ret, NULL, 0);

} // execute 
