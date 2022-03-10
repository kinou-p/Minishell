/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:33:30 by apommier          #+#    #+#             */
/*   Updated: 2022/03/10 01:32:44 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void exit_shell(t_cmd *cmd)
{
	cmd = 0;
	exit(1);
}

void free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->s_cmds[i])
	{
		free_double(cmd->s_cmds[i]->args);
		free(cmd->s_cmds[i]->cmd);
		if (cmd->s_cmds[i]->infile)
			free(cmd->s_cmds[i]->infile);
		if (cmd->s_cmds[i]->outfile)
			free(cmd->s_cmds[i]->outfile);
		free(cmd->s_cmds[i]);
		i++;
	}
	free_double(cmd->path);
	free(cmd->s_cmds);
	free(cmd);
}