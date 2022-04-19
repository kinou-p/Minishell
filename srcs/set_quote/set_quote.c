/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:58:21 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 13:00:38 by apommier         ###   ########.fr       */
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
		if (str[i] == '\'' && open != 2)
		{
			if (!open)
				open = 1;
			else if (open == 1)
				open = 0;
			simple_quote++;
		}
		else if (str[i] == '"' && open != 1)
		{
			if (!open)
				open = 2;
			else if (open == 2)
				open = 0;
			double_quote++;
		}
		i++;
	}
	if (simple_quote % 2 || double_quote % 2)
		return (0);
	return (1);
}

char	*del_char(char *str, int *index)
{
	char	*swap;
	char	*swap2;

	swap = 0;
	swap = ft_strdup(str + *index + 1);
	str[*index] = 0;
	swap2 = str;
	str = ft_strjoin(str, swap);
	free(swap2);
	free(swap);
	return (str);
}

char	*get_var(t_cmd	*cmd, char *var_name)
{
	char	*line;
	char	**split_line;
	int		index;

	line = 0;
	if (!ft_strcmp(var_name, "?"))
		return (ft_itoa(cmd->err_var));
	index = find_it(cmd->env, var_name);
	if (index >= 0)
	{
		line = cmd->env[index];
		split_line = ft_split(line, '=');
		if (split_line[1])
			line = ft_strdup(split_line[1]);
		else
			return (0);
		free_double(split_line);
	}
	return (line);
}

char	*change_var(t_cmd *big_cmd, char *cmd, int *index)
{
	int		i;
	char	*swap;
	char	*swap2;
	char	*ret;
	char	*var;

	i = *index + 1;
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '?'))
		i++;
	swap = ft_substr(cmd, *index + 1, i - *index - 1);
	var = get_var(big_cmd, swap);
	free(swap);
	swap2 = ft_strdup(cmd + i);
	cmd[*index] = 0;
	ret = ft_strjoin(cmd, var);
	free(cmd);
	*index += ft_strlen(var) - 1;
	free(var);
	var = ret;
	ret = ft_strjoin(ret, swap2);
	free(var);
	free(swap2);
	return (ret);
}

char	*set_var(t_cmd *big_cmd, char *cmd)
{
	int		i;
	char	*del;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{	
			cmd = del_char(cmd, &i);
			if (cmd[i])
			{
				while (cmd[i] != '\'')
				{
					i++;
				}
				cmd = del_char(cmd, &i);
			}
		}
		else if (cmd[i] == '"')
		{
			cmd = del_char(cmd, &i);
			if (cmd[i])
			{
				while (cmd[i] != '"')
				{	
					if (cmd[i] == '$')
						cmd = change_var(big_cmd, cmd, &i);
					i++;
				}
				cmd = del_char(cmd, &i);
			}
		}
		else if (cmd[i] == '$')
			cmd = change_var(big_cmd, cmd, &i);
		else
			i++;
	}
	return (cmd);
}

int	parse_quote(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*swap;

	i = 0;
	while (cmd->s_cmds[i])
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
		i++;
	}
	return (0);
}
