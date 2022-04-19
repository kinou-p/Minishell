/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:58:21 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 17:19:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_quote(char *str, int index)
{
	int	i;
	int	open;

	open = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\'' && open != 2)
		{
			if (!open)
				open = 1;
			else if (open == 1)
				open = 0;
		}
		else if (str[i] == '"' && open != 1)
		{
			if (!open)
				open = 2;
			else if (open == 2)
				open = 0;
		}
		i++;
	}
	return (open);
}

void	count_quote(char c, int *open, int *simple_quote, int *double_quote)
{
	if (c == '\'' && *open != 2)
	{
		if (!(*open))
			(*open) = 1;
		else if ((*open) == 1)
			(*open) = 0;
		(*simple_quote)++;
	}
	else if (c == '"' && (*open) != 1)
	{
		if (!(*open))
			(*open) = 2;
		else if ((*open) == 2)
			(*open) = 0;
		(*double_quote)++;
	}
}

int	is_quote_good(char *str)
{
	int	simple_quote;
	int	double_quote;
	int	open;
	int	i;

	i = 0;
	open = 0;
	simple_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		count_quote(str[i], &open, &simple_quote, &double_quote);
		i++;
	}
	if (simple_quote % 2 || double_quote % 2)
		return (0);
	return (1);
}

int	parse_quote(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*swap;

	i = -1;
	while (cmd->s_cmds[++i])
	{		
		j = -1;
		while (cmd->s_cmds[i]->args[++j])
		{
			swap = cmd->s_cmds[i]->args[j];
			cmd->s_cmds[i]->args[j] = set_var(cmd, cmd->s_cmds[i]->args[j]);
		}
		if (!is_builtin(cmd->s_cmds[i]->args[0]))
		{
			cmd->s_cmds[i]->cmd = get_command(cmd->s_cmds[i]->args, cmd->path);
			if (cmd->s_cmds[i]->cmd == cmd->s_cmds[i]->args[0])
				cmd->s_cmds[i]->cmd = ft_strdup(cmd->s_cmds[i]->cmd);
		}
		else
			cmd->s_cmds[i]->cmd = ft_strdup(cmd->s_cmds[i]->args[0]);
		if (!cmd->s_cmds[i]->cmd)
			cmd->s_cmds[i]->cmd = ft_strdup(cmd->s_cmds[i]->args[0]);
	}
	return (0);
}
