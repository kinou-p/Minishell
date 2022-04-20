/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:12:52 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/20 12:46:41 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

void	call_builtin(t_cmd *cmd)
{
	dup2(cmd->current_s_cmd->fd[0], 0);
	dup2(cmd->current_s_cmd->fd[1], 1);
	close(cmd->current_s_cmd->fd[0]);
	close(cmd->current_s_cmd->fd[1]);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "exit"))
		ft_exit(cmd->current_s_cmd);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "env"))
		print_env(cmd);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "export"))
		ft_export(cmd->current_s_cmd);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "unset"))
		ft_unset(cmd->current_s_cmd);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "echo"))
		ft_echo(cmd->current_s_cmd);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "cd"))
		open_directory(cmd->current_s_cmd);
	if (!ft_strcmp(cmd->current_s_cmd->cmd, "pwd"))
		ft_pwd(cmd->current_s_cmd);
}
