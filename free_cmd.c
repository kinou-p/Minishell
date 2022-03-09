/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:33:30 by apommier          #+#    #+#             */
/*   Updated: 2022/03/09 13:58:03 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit(1);
}

void free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("free_cmd\n");
	while (cmd->s_cmds[i])
	{
		free_double(cmd->s_cmds[i]->args);
		free(cmd->s_cmds[i]->cmd);
		free(cmd->s_cmds[i]);
		i++;
	}
	free_double(cmd->path);
	free(cmd->s_cmds);
	free(cmd);
}